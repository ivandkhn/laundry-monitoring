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

#include "packetbuf.h"
#include "contiki.h"
#include "dev/leds.h"
#include "platform/zoul/dev/adc-zoul.h"
#include "net/netstack.h"
#include "net/rime/rime.h"
#include "etimer.h"
#include "ctimer.h"
#include "project-conf.h"

#include "stdio.h"
#include "helpers.h"
#include "packet.h"
#include "edge.h"

// TODO: check it's equal to gateway node id
const linkaddr_t GATEWAY_ADDR = {.u8[0] = 0, .u8[1] = 9};

/**
 * Callback function for issuing EDGE_ANNOUNCE messages.
 *
 * Every Q_STATUS message from GW resets the callback timer. If GW
 * node did not communicate with edge node long enough, then the
 * timer expires and a new announcement is issued.
 */
void announceCallback() {
    packet_t txPacket;

    txPacket.via.u8[0] = 0;
    txPacket.via.u8[1] = linkaddr_node_addr.u8[1];
    txPacket.operation = EDGE_ANNOUNCE;

    sendUnicast("Edge sends", &txPacket, &unicast, GATEWAY_ADDR);
    ctimer_restart(&edgeAnnounceTimer);
}

/**
 * Callback for unicast reception.
 *
 * @param c Current unicast connection.
 * @param from Source address of the unicast message.
 */
void unicast_recv(struct unicast_conn *c, const linkaddr_t *from) {
    packet_t txPacket;

    packetbuf_copyto(&txPacket);

    printf("Unicast message received from 0x%x%x: '%s' [RSSI %d]\n",
           from->u8[0], from->u8[1],
           (char *)packetbuf_dataptr(),
           (int16_t)packetbuf_attr(PACKETBUF_ATTR_RSSI));

    linkaddr_t unicastDst;
    switch (txPacket.operation) {
        case Q_STATUS:
            unicastDst = txPacket.machineAddr;
            ctimer_restart(&edgeAnnounceTimer);
            break;
        case A_STATUS:
            unicastDst = txPacket.src;
            break;
        case EDGE_ANNOUNCE:
            printf("Edge mode unexpectedly received EDGE_ANNOUNCE!\n");
            return;
    }

    sendUnicast("Edge sending", &txPacket, &unicast, unicastDst);
}

/**
 * Callback execute after unicast transmission, thr latter being
 * possibly unsuccessful.
 *
 * @param ptr Current unicast connection.
 * @param status Result code of transmission – non-zero code means
 * the message was NOT successfully transmitted.
 * @param num_tx Number of executed re-transmissions.
 */
static void unicast_sent(struct unicast_conn *ptr, int status, int num_tx) {
    const linkaddr_t* addr = packetbuf_addr(PACKETBUF_ADDR_RECEIVER);
    printf("Send done to %d.%d: status %d, num_tx %i\n", addr->u8[0], addr->u8[1], status, num_tx);
    if (status != 0) {
        packet_t txPacket;

        txPacket.via.u8[0] = 0;
        txPacket.via.u8[1] = linkaddr_node_addr.u8[1];
        txPacket.src = GATEWAY_ADDR;
        txPacket.operation = A_STATUS;
        txPacket.machineStatus = STATUS_UNKNOWN;
        txPacket.machineAddr = *addr;

        sendUnicast("Edge sends", &txPacket, &unicast, GATEWAY_ADDR);
    }
}

static const struct unicast_callbacks unicast_call = {unicast_recv, unicast_sent};

PROCESS (mainProcess, "Main");
AUTOSTART_PROCESSES (&mainProcess);
PROCESS_THREAD (mainProcess, ev, data) {
	PROCESS_BEGIN ();

    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_CHANNEL, TX_CHANNEL);
    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_TXPOWER, TX_POWER);
    unicast_open(&unicast, 129, &unicast_call);
    ctimer_set(&edgeAnnounceTimer, ANNOUNCE_TIME_THRESHOLD, &announceCallback, NULL);

    while (1) {
		PROCESS_WAIT_EVENT();
    }

	PROCESS_END ();
}
