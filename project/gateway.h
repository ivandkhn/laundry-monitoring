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

#ifndef PROJECT_GATEWAY_H
#define PROJECT_GATEWAY_H

#include "packetbuf.h"
#include "contiki.h"
#include "dev/leds.h"
#include "platform/zoul/dev/adc-zoul.h"
#include "net/netstack.h"
#include "net/rime/rime.h"
#include "etimer.h"
#include "ctimer.h"

static struct unicast_conn unicast;
static void unicast_recv(struct unicast_conn *c, const linkaddr_t *from);

#define POLL_INTERVAL (CLOCK_SECOND*2)
static struct ctimer pollingTimer;
static void pollingCallback();

#define MAX_EDGE_ADDRESSES 2
static linkaddr_t edge_addresses[MAX_EDGE_ADDRESSES];
static uint8_t totalEdgeAddresses = 0, currentEdgeAddressIdx = 0;

#define MAX_MACHINE_ADDRESSES 6
static uint8_t currentMachineAddress = 0;

#endif //PROJECT_GATEWAY_H
