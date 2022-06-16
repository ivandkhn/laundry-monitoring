/*
   Wireless Sensor Networks Laboratory

   Technische Universität München
   Lehrstuhl für Kommunikationsnetze
   http://www.lkn.ei.tum.de
*/

#include "stdint.h"
#include "dev/leds.h"
#include "helpers.h"


void setLedStatus(uint8_t color) {
    leds_off(LEDS_ALL);
    leds_on(color);
}
