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

#ifndef PROJECT_EDGE_H
#define PROJECT_EDGE_H

#define ANNOUNCE_TIME_THRESHOLD (CLOCK_SECOND*5)
static struct ctimer edgeAnnounceTimer;
static void announceCallback();

static struct unicast_conn unicast;
static void unicast_recv(struct unicast_conn *c, const linkaddr_t *from);

#endif //PROJECT_EDGE_H
