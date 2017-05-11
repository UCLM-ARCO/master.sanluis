#include "contiki.h"
#include "core/dev/leds.h"

PROCESS(myejemplo, "Mi primer proceso");
AUTOSTART_PROCESSES(&myejemplo);

PROCESS_THREAD(myejemplo, ev, data)
{
  static struct etimer periodic;
  PROCESS_BEGIN();
  etimer_set(&periodic, CLOCK_SECOND*2); 
  while(1){
    leds_on(LEDS_GREEN);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic));
    etimer_reset(&periodic);
    leds_off(LEDS_GREEN);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&periodic));
    etimer_reset(&periodic);
  }
  PROCESS_END();
}

