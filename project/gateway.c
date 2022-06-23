//
// Created by Ivan Dakhnenko on 23.06.22.
//

#include "gateway.h"
#include "packet.h"
#include "stdio.h"

static const struct unicast_callbacks unicast_call = {unicast_recv};
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
            printf("Gateway unexpectedly received Q_STATUS\n");
        case A_STATUS:
            printPacket("Gateway received", rxPacket);
    }
}

static void pollingCallback(){
    ctimer_reset(&pollingTimer);
    if (totalEdgeAddresses == 0) {
        return;
    }

    packet_t txPacket;
    txPacket.operation = Q_STATUS;
    linkaddr_t viaAddr = edge_addresses[currentEdgeAddressIdx];
    txPacket.via = viaAddr;
    txPacket.src.u8[0] = 0;
    txPacket.src.u8[1] = linkaddr_node_addr.u8[1];

    currenMachineAddress++;
    if (currenMachineAddress > MAX_MACHINE_ADDRESSES) {
        currenMachineAddress = 1;
    }
    linkaddr_t machineAddr = {.u8[0] = 0, .u8[1] = currenMachineAddress};
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
		PROCESS_WAIT_EVENT();
    }

	PROCESS_END ();
}


