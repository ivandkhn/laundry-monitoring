/*
   Wireless Sensor Networks Laboratory

   Technische Universität München
   Lehrstuhl für Kommunikationsnetze
   http://www.lkn.ei.tum.de

   copyright (c) 2017 Chair of Communication Networks, TUM

   contributors:
   * Thomas Szyrkowiec
   * Mikhail Vilgelm
   * Octavio Rodríguez Cervantes
   * Angel Corona

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, version 2.0 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   LESSON 1: Multithreading
*/

// Contiki-specific includes:
#include "contiki.h"
#include "dev/leds.h" // Enables use of LEDs.

// Standard C includes:
#include <stdio.h>    // For printf.

/**
 * Define timings for different colors.
 */
const u_int32_t RED_BLINK_INTERVAL = CLOCK_SECOND;
const u_int32_t GREEN_BLINK_INTERVAL = CLOCK_SECOND / 2;
const u_int32_t BLUE_BLINK_INTERVAL = CLOCK_SECOND / 4;
const u_int32_t RED_STOP_INTERVAL = CLOCK_SECOND * 2;

/**
 * Timers to control corresponding colors.
 */
static struct etimer timerRed, timerGreen, timerBlue, timerRedTerminate;

//--------------------- PROCESS CONTROL BLOCK ---------------------
PROCESS(red_led_process, "Control red LED");
PROCESS(green_led_process, "Control green LED");
PROCESS(blue_led_process, "Control blue LED");
PROCESS(terminate_red_process, "Terminate red LED blinking");
AUTOSTART_PROCESSES(&red_led_process, &green_led_process,
                    &blue_led_process, &terminate_red_process);

//------------------------ PROCESS' THREAD ------------------------
PROCESS_THREAD(red_led_process, ev, data) {
    PROCESS_BEGIN();
    etimer_set(&timerRed, RED_BLINK_INTERVAL);
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timerRed));
        leds_toggle(LEDS_RED);
        etimer_reset(&timerRed);
    }
    PROCESS_END();
}

PROCESS_THREAD(green_led_process, ev, data) {
    PROCESS_BEGIN();
    etimer_set(&timerGreen, GREEN_BLINK_INTERVAL);
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timerGreen));
        leds_toggle(LEDS_GREEN);
        etimer_reset(&timerGreen);
    }
    PROCESS_END();
}

PROCESS_THREAD(blue_led_process, ev, data) {
    PROCESS_BEGIN();
    etimer_set(&timerBlue, BLUE_BLINK_INTERVAL);
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timerBlue));
        leds_toggle(LEDS_BLUE);
        etimer_reset(&timerBlue);
    }
    PROCESS_END();
}

PROCESS_THREAD(terminate_red_process, ev, data) {
    PROCESS_BEGIN();
    etimer_set(&timerRedTerminate, RED_STOP_INTERVAL);
    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timerRedTerminate));
        leds_off(LEDS_RED);
        process_exit(&red_led_process);
        etimer_stop(&timerRed);
    }
    PROCESS_END();
}
