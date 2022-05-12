// Contiki-specific includes:
#include "contiki.h"
#include "dev/leds.h"
#include "dev/button-sensor.h"
#include "dev/serial-line.h"

//--------------------- PROCESS CONTROL BLOCK ---------------------
PROCESS(first_process, "Main process of the first WSN lab application");
AUTOSTART_PROCESSES(&first_process);

//------------------------ PROCESS' THREAD ------------------------
PROCESS_THREAD(first_process, ev, data)
{
    PROCESS_BEGIN();

    leds_off(LEDS_ALL);
    button_sensor.configure(BUTTON_SENSOR_CONFIG_TYPE_INTERVAL, CLOCK_SECOND*2);

    while(1) {

        PROCESS_WAIT_EVENT();

        if(ev == sensors_event) {
            /* Process event from sensors, in our case, button sensor is used */
            if (data == &button_sensor) {
                if (button_sensor.value(BUTTON_SENSOR_VALUE_TYPE_LEVEL) ==
                    BUTTON_SENSOR_PRESSED_LEVEL) {
                    leds_on(LEDS_RED);
                } else if (button_sensor.value(BUTTON_SENSOR_VALUE_TYPE_LEVEL) ==
                           BUTTON_SENSOR_RELEASED_LEVEL) {
                    leds_off(LEDS_RED);
                    leds_off(LEDS_GREEN);
                }
            }
        } else if (ev == button_press_duration_exceeded) {
            leds_toggle(LEDS_RED);
            leds_toggle(LEDS_GREEN);
        } else if (ev == serial_line_event_message) {
            /* Parse transmitted string and turn on/off corresponding LEDs. */
            if (strncmp(data, "red.on", 6) == 0) {
                leds_on(LEDS_RED);
            } else if (strncmp(data, "red.off", 7) == 0) {
                leds_off(LEDS_RED);
            } else if (strncmp(data, "green.on", 8) == 0) {
                leds_on(LEDS_GREEN);
            } else if (strncmp(data, "green.off", 9) == 0) {
                leds_off(LEDS_GREEN);
            } else if (strncmp(data, "blue.on", 7) == 0) {
                leds_on(LEDS_BLUE);
            } else if (strncmp(data, "blue.off", 8) == 0) {
                leds_off(LEDS_BLUE);
            }
        }
    }

    PROCESS_END();
}
