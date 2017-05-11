#include "contiki.h"
#include "core/dev/leds.h"
#include "core/dev/button-sensor.h"

PROCESS(pulsador, "Pulsador");
AUTOSTART_PROCESSES(&pulsador);

PROCESS_THREAD(pulsador, ev, data)
{
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(button_sensor);
  while(1){
    leds_on(LEDS_GREEN);
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor); 
    leds_off(LEDS_GREEN);
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor);
  }
  PROCESS_END();
}

