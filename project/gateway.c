//
// Created by Ivan Dakhnenko on 23.06.22.
//

#include "gateway.h"
#include "packet.h"
#include "stdio.h"

static const struct unicast_callbacks unicast_call = {unicast_recv};
/**
 * Callback for unicast reception. Here, we look at operation of the
 * received packet and choose the appropriate action.
 *
 * @param c Current unicast connection.
 * @param from Source address of the unicast message.
 */
static void unicast_recv(struct unicast_conn *c, const linkaddr_t *from) {
    packet_t rxPacket;

    packetbuf_copyto(&rxPacket);

    printf("Unicast message received from 0x%x%x: '%s' [RSSI %d]\n",
           from->u8[0], from->u8[1],
           (char *)packetbuf_dataptr(),
           (int16_t)packetbuf_attr(PACKETBUF_ATTR_RSSI));

    switch (rxPacket.operation) {
        case EDGE_ANNOUNCE:
            totalEdgeAddresses++;
            edge_addresses[totalEdgeAddresses-1] = rxPacket.via;
            currentEdgeAddressIdx = totalEdgeAddresses-1;
            // TODO: check stability in case of multiple EDGE_ANNOUNCES from the same edge
            printf("EDGE_ANNOUNCE received, totalEdgeAddresses = %d\n", totalEdgeAddresses);
            break;
        case Q_STATUS:
            // Gateway mode only issues Q_STATUS, but should not receive them, since
            // they are replaced with A_STATUS by the sensor or edge.
            printf("Gateway unexpectedly received Q_STATUS\n");
        case A_STATUS:
            // Print and parse in the UI.
            printPacket("Gateway received", rxPacket);
    }
}

/**
 * Callback for issuing Q_STATUS messages.
 *
 * Gateway mote queries the status of the machines one by one,
 * selecting the Edge mote in a Round-robin manner.
 */
static void pollingCallback(){
    ctimer_reset(&pollingTimer);
    if (totalEdgeAddresses == 0) {
        // No EDGE_ANNOUNCE has been received yet.
        return;
    }

    packet_t txPacket;
    txPacket.operation = Q_STATUS;
    linkaddr_t viaAddr = edge_addresses[currentEdgeAddressIdx];
    txPacket.via = viaAddr;
    txPacket.src.u8[0] = 0;
    txPacket.src.u8[1] = linkaddr_node_addr.u8[1];

    // Wrap currentMachineAddress at MAX_MACHINE_ADDRESSES back to 1.
    currentMachineAddress++;
    if (currentMachineAddress > MAX_MACHINE_ADDRESSES) {
        currentMachineAddress = 1;
    }

    linkaddr_t machineAddr = {.u8[0] = 0, .u8[1] = currentMachineAddress};
    txPacket.machineAddr = machineAddr;

    sendUnicast("Gateway sends", &txPacket, &unicast, viaAddr);
}

PROCESS (gatewayMainProcess, "Main");
AUTOSTART_PROCESSES (&gatewayMainProcess);
PROCESS_THREAD (gatewayMainProcess, ev, data) {
	PROCESS_BEGIN ();

    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_CHANNEL, 15);
    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_TXPOWER, 5);
    unicast_open(&unicast, 129, &unicast_call);
    ctimer_set(&pollingTimer, POLL_INTERVAL, &pollingCallback, NULL);

    while (1) {
        // Waiting for either unicast_call or pollingCallback.
		PROCESS_WAIT_EVENT();
    }

	PROCESS_END ();
}


