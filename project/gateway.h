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
#include "edgepool.h"

static struct unicast_conn unicast;
static void unicast_recv(struct unicast_conn *c, const linkaddr_t *from);
static void unicast_sent(struct unicast_conn *ptr, int status, int num_tx);

#define POLL_INTERVAL (CLOCK_SECOND*1)
static struct ctimer pollingTimer;
static void pollingCallback();

static edgePool_t edgePool = {.currentAddress = 0, .validAddresses = 0};

#define MAX_MACHINE_ADDRESSES 6
static uint8_t currentMachineAddress = 0;

#endif //PROJECT_GATEWAY_H
