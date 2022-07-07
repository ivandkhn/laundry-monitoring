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

#include "packetbuf.h"
#include "contiki.h"
#include "dev/leds.h"
#include "platform/zoul/dev/adc-zoul.h"
#include "net/netstack.h"
#include "net/rime/rime.h"
#include "etimer.h"

#include "stdio.h"
#include "helpers.h"
#include "packet.h"

/*
 * CLion complains a lot about definitions of ZOUL_SENSORS_XXX, since
 * code completion engine evaluates them all to zero. I include the
 * following pragmas to disable IDE warnings.
 */
#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnreachableCode"
#pragma ide diagnostic ignored "bugprone-branch-clone"
/**
 * Read raw sensor value.
 *
 * @param sensorId ID of a sensor, e.g. ZOUL_SENSORS_ADC1.
 * @return Raw int value read from a sensor.
 */
static int readSensorValue(int sensorId) {
    int sensorValue = adc_zoul.value(sensorId) >> 4;

    if (sensorId == ZOUL_SENSORS_ADC1) {
        printf("Read data from ZOUL_SENSORS_ADC1: [%i]\n", sensorValue);
    } else if (sensorId == ZOUL_SENSORS_ADC3) {
        printf("Read data from ZOUL_SENSORS_ADC3: [%i]\n", sensorValue);
    } else {
        printf("Read data from ZOUL_SENSOR: [%i]\n", sensorValue);
    }

    return sensorValue;
}
#pragma clang diagnostic pop

#define LIGHT_SENSOR_THRESHOLD 1000
#define VIBRATION_SENSOR_THRESHOLD 300
/**
 * Read sensor values and determine machine status base on it.
 *
 * @return Status of the machine.
 */
static machineStatus_t getMachineStatus() {
    int adc1Value = readSensorValue(ZOUL_SENSORS_ADC1);
    int adc3Value = readSensorValue(ZOUL_SENSORS_ADC3);
    if (adc3Value < LIGHT_SENSOR_THRESHOLD) {
        setLedStatus(LEDS_GREEN);
        printf("Set machine status to STATUS_FREE\n");
        return STATUS_FREE;
    } else if (adc1Value < VIBRATION_SENSOR_THRESHOLD) {
        setLedStatus(LEDS_YELLOW);
        printf("Set machine status to STATUS_FINISHING\n");
        return STATUS_FINISHING;
    } else {
        setLedStatus(LEDS_RED);
        printf("Set machine status to STATUS_BUSY\n");
        return STATUS_BUSY;
    }
}

static struct unicast_conn unicast;
/**
 * Callback for unicast reception.
 *
 * @param c Current unicast connection.
 * @param from Source address of the unicast message.
 */
static void unicast_recv(struct unicast_conn *c, const linkaddr_t *from) {
    packet_t tx_packet;

    packetbuf_copyto(&tx_packet);

    printf("Unicast message received from 0x%x%x: '%s' [RSSI %d]\n",
           from->u8[0], from->u8[1],
           (char *)packetbuf_dataptr(),
           (int16_t)packetbuf_attr(PACKETBUF_ATTR_RSSI));

    switch (tx_packet.operation) {
        case Q_STATUS:
            tx_packet.machineStatus = getMachineStatus();
            tx_packet.operation = A_STATUS;
            break;
        default:
            printf("Unknown query operation [%i] received!\n", tx_packet.operation);
            return;
    }

    sendUnicast("Sensor sends", &tx_packet, &unicast, tx_packet.via);

}
static const struct unicast_callbacks unicast_call = {unicast_recv};


PROCESS (mainProcess, "Main");
AUTOSTART_PROCESSES (&mainProcess);
PROCESS_THREAD (mainProcess, ev, data) {
    PROCESS_BEGIN ();

    adc_zoul.configure(SENSORS_HW_INIT, ZOUL_SENSORS_ADC1 | ZOUL_SENSORS_ADC3);
	NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_CHANNEL, 15);
    NETSTACK_CONF_RADIO.set_value(RADIO_PARAM_TXPOWER, 5);
    unicast_open(&unicast, 129, &unicast_call);

    while (1) {
		PROCESS_WAIT_EVENT();
    }

	PROCESS_END ();
}

