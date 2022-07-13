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
#include "dev/leds.h"
#include "net/rime/rime.h"
#include "packet.h"

/**
 * Pretty-print the packet into serial line.
 *
 * @param prefix Arbitrary string to print before the packet contents.
 * @param packet The packet itself.
 */
void printPacket(char *prefix, packet_t packet) {
    printf("%s ", prefix);
    printf("packet: {\n");
    switch (packet.operation) {
        case EDGE_ANNOUNCE:
            printf("\toperation: EDGE_ANNOUNCE\n");
            break;
        case Q_STATUS:
            printf("\toperation: Q_STATUS\n");
            break;
        case A_STATUS:
            printf("\toperation: A_STATUS\n");
            break;
    }
    printf("\tsrc: 0x%x%x\n", packet.src.u8[0], packet.src.u8[1]);
    printf("\tvia: 0x%x%x\n", packet.via.u8[0], packet.via.u8[1]);
    printf("\tmachineAddr: 0x%x%x\n", packet.machineAddr.u8[0], packet.machineAddr.u8[1]);
    switch (packet.machineStatus) {
        case STATUS_FREE:
            printf("\tstatus: STATUS_FREE\n");
            break;
        case STATUS_FINISHING:
            printf("\tstatus: STATUS_FINISHING\n");
            break;
        case STATUS_BUSY:
            printf("\tstatus: STATUS_BUSY\n");
            break;
        case STATUS_UNKNOWN:
            printf("\tstatus: STATUS_UNKNOWN\n");
            break;
    }
    printf("}\n");
}

/**
 * Custom wrapper for issuing unicast messages.
 *
 * @param prefix Arbitrary string to print before the packet contents.
 * @param txPacket The packet for transmission.
 * @param u Current unicast connection.
 * @param dst Destination address.
 */
void sendUnicast(char *prefix, packet_t *txPacket, struct unicast_conn *u, linkaddr_t dst) {
    packetbuf_copyfrom(txPacket, sizeof((*txPacket)));
    printPacket(prefix, (*txPacket));
    leds_on(LEDS_BLUE);
    rtimer_clock_t end = RTIMER_NOW() + RTIMER_SECOND / 20;
    while(RTIMER_CLOCK_LT(RTIMER_NOW(), end)) { /* pause */}
    unicast_send(u, &dst);
    leds_off(LEDS_BLUE);
}
