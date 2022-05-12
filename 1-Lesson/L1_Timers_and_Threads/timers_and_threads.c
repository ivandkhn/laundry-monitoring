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

   LESSON 1: Timers and Threads
*/


// Contiki-specific includes:
#include "contiki.h"
#include "dev/leds.h"
#include "sys/ctimer.h"
#include "sys/etimer.h"

// Standard C includes:
#include <stdio.h>

/**
 * Define timings for different colors.
 */
const u_int32_t RED_BLINK_INTERVAL = CLOCK_SECOND;
const u_int32_t BLUE_BLINK_INTERVAL = CLOCK_SECOND / 2;
const u_int32_t RED_STOP_INTERVAL = CLOCK_SECOND * 5;

/**
 * Process to control blinking of red LED.
 */
PROCESS(red_led_process, "Control blinking of red LED");

/**
 * Process to control blinking of blue LED.
 */
PROCESS(blue_led_process, "Control blinking of blue LED");

/**
 * Process to terminate blinking of red LED after certain period.
 */
PROCESS(terminate_red_process, "Terminate blinking of blue LED");

/**
 * Launch all processes on startup.
 */
AUTOSTART_PROCESSES(&red_led_process, &blue_led_process, &terminate_red_process);

/**
 * Callback-based timer to blink red LED.
 */
static struct ctimer ct;

/**
 * Event-based timer to blink blue LED.
 */
static struct etimer et;

/**
 * Event-based timer to stop blinking red LED.
 */
static struct etimer et_term;

/**
 * Callback to toggle state of red LED.
 */
static void callback_function(void *data) {
    leds_toggle(LEDS_RED);
    ctimer_reset(&ct);
}

//------------------------ PROCESS' THREAD ------------------------
PROCESS_THREAD(red_led_process, ev, data) {
    PROCESS_BEGIN();

    /* Map ctimer to callback function */
    ctimer_set(&ct, RED_BLINK_INTERVAL, callback_function, NULL);

    while (1){
        PROCESS_WAIT_EVENT();
    }

    PROCESS_END();
}

PROCESS_THREAD(blue_led_process, ev, data) {
    PROCESS_BEGIN();

    etimer_set(&et, BLUE_BLINK_INTERVAL);

    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
        leds_toggle(LEDS_BLUE);
        etimer_reset(&et);
    }

    PROCESS_END();
}

PROCESS_THREAD(terminate_red_process, ev, data) {
    PROCESS_BEGIN();

    etimer_set(&et_term, RED_STOP_INTERVAL);

    while(1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et_term));
        leds_off(LEDS_RED);
        process_exit(&red_led_process);
        ctimer_stop(&ct);
    }

    PROCESS_END();
}
