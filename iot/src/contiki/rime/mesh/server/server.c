#include "contiki.h"
#include "core/net/rime/rime.h"
#include "core/net/rime/mesh.h"

#include "core/dev/button-sensor.h"

#include "core/dev/leds.h"

#include <stdio.h>
#include <string.h>


#define COMUNICATION_CHANNEL 1000
#define ON 1
#define OFF 0

void cambio(int status);
static struct mesh_conn mesh;


static void snd(struct mesh_conn *c){
  return;
}
static void timeout(struct mesh_conn *c){
  return;
}
static void rcv(struct mesh_conn *c, const linkaddr_t *from, uint8_t hops){
  printf("Recibido paquete\n");
  cambio(ON);
  return;
}

const static struct mesh_callbacks callbacks = {rcv, snd, timeout};

PROCESS(server, "Servidor");
AUTOSTART_PROCESSES(&server);
PROCESS_THREAD(server, ev, data)
{
  PROCESS_EXITHANDLER(mesh_close(&mesh));
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(button_sensor);
  static struct etimer timer;
  mesh_open(&mesh, COMUNICATION_CHANNEL, &callbacks);
  etimer_set(&timer, 10*CLOCK_SECOND);
  while(1){
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));
    etimer_reset(&timer);
    cambio(OFF);
  }
  PROCESS_END();
}

void cambio(int status){
  if(status==ON) leds_on(LEDS_GREEN);
  if(status==OFF) leds_off(LEDS_GREEN);
}
