/*
    Copyright (c) 2022 Group 5, SDN Lab

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2.0 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "gateway.h"
#include "packet.h"
#include "stdio.h"
#include "project-conf.h"

static const struct unicast_callbacks unicast_call = {unicast_recv, unicast_sent};
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

    switch (rxPacket.operation) {
        case EDGE_ANNOUNCE:
            poolAdd(&edgePool,rxPacket.via);
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
 * Callback for unicast transmission completion. If the last transmission was
 * unsuccessful, we mark the midpoint in the network (i.e. the edge address)
 * as invalid, so that we will not be sending via this node anymore – until
 * we receive a new EDGE_ANNOUNCE.
 *
 * @param c Current unicast connection.
 * @param status Result code of transmission – non-zero code means
 * the message was NOT successfully transmitted.
 * @param num_tx Number of executed re-transmissions.
 */
static void unicast_sent(struct unicast_conn *ptr, int status, int num_tx) {
    const linkaddr_t* addr = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
    printf("Send done to %d.%d: status %d, num_tx %i\n", addr->u8[0], addr->u8[1], status, num_tx);
    if (status != 0) {
        poolRemove(&edgePool, *addr);
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
    if (edgePool.validAddresses == 0) {
        // No EDGE_ANNOUNCE has been received yet.
        return;
    }

    packet_t txPacket;
    txPacket.operation = Q_STATUS;
    linkaddr_t viaAddr = poolGet(&edgePool);
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

    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_CHANNEL, TX_CHANNEL);
    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_TXPOWER, TX_POWER);
    unicast_open(&unicast, 129, &unicast_call);
    ctimer_set(&pollingTimer, POLL_INTERVAL, &pollingCallback, NULL);

    while (1) {
        // Waiting for either unicast_call or pollingCallback.
		PROCESS_WAIT_EVENT();
    }

	PROCESS_END ();
}


