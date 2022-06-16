/*
   Wireless Sensor Networks Laboratory

   Technische Universität München
   Lehrstuhl für Kommunikationsnetze
   http://www.lkn.ei.tum.de
*/

#ifndef PROJECT_SENSOR_H
#define PROJECT_SENSOR_H

#include "core/net/linkaddr.h"

typedef enum {
    STATUS_FREE,
    STATUS_FINISHING,
    STATUS_BUSY
} machineStatus_t;

typedef enum {
    QUERY_STATUS
} queryOperation_t;

typedef struct {
    linkaddr_t src;
    queryOperation_t operation;
} rxPacket_t;

typedef struct {
    machineStatus_t machineStatus;
} txPacket_t;

#endif //PROJECT_SENSOR_H
