//
// Created by Ivan Dakhnenko on 23.06.22.
//

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
