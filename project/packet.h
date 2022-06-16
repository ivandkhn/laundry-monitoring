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

#ifndef PROJECT_PACKET_H
#define PROJECT_PACKET_H

#include "core/net/linkaddr.h"
#include "stdio.h"

typedef enum {
    STATUS_FREE,
    STATUS_FINISHING,
    STATUS_BUSY,
    STATUS_UNKNOWN
} machineStatus_t;

typedef enum {
    EDGE_ANNOUNCE,
    Q_STATUS,
    A_STATUS,
} operation_t;

typedef struct {
    operation_t operation;
    linkaddr_t src;
    linkaddr_t via;
    linkaddr_t machineAddr;
    machineStatus_t machineStatus;
} packet_t;

void printPacket(char * prefix, packet_t packet);
void sendUnicast(char *prefix, packet_t *txPacket, struct unicast_conn *u, linkaddr_t dst);

#endif //PROJECT_PACKET_H
