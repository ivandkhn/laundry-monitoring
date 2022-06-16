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

#include "packet.h"

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
    printf("\tsrc: 0x%x\n", packet.src.u8[1]);
    printf("\tvia: 0x%x\n", packet.via.u8[1]);
    printf("\tmachineId: %d\n", packet.machineId);
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
    printf("}");
}
