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

#ifndef PROJECT_EDGEPOOL_H
#define PROJECT_EDGEPOOL_H

#include "edgepool.h"
#include "linkaddr.h"

#define MAX_EDGE_ADDRESSES 2
typedef struct {
    linkaddr_t addresses[MAX_EDGE_ADDRESSES];
    uint8_t validAddresses;
    uint8_t currentAddress;
} edgePool_t;

void poolAdd(edgePool_t *pool, linkaddr_t addr);
void poolRemove(edgePool_t *pool, linkaddr_t addr);
linkaddr_t poolGet(edgePool_t *pool);

#endif //PROJECT_EDGEPOOL_H
