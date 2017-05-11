#include "contiki.h"
#include "core/dev/leds.h"

PROCESS(ejemploled, "Mi primer proceso");
AUTOSTART_PROCESSES(&ejemploled);

PROCESS_THREAD(ejemploled, ev, data)
{
  
  PROCESS_BEGIN();
  
    leds_on(LEDS_GREEN);
  
  PROCESS_END();
}

