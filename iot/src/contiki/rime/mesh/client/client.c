#include "contiki.h"
#include "core/net/rime/rime.h"
#include "core/dev/button-sensor.h"
#include "core/net/rime/mesh.h"
#include "stdio.h"
#define COMUNICATION_CHANNEL 1000

static struct mesh_conn mesh;
linkaddr_t dst;

struct msg{
  int type;
};

struct msg mensaje;

static void snd(struct mesh_conn *c){
  return;
}
static void timeout(struct mesh_conn *c){
  return;
}
static void rcv(struct mesh_conn *c, const linkaddr_t *from, uint8_t hops){
  return;
}

const static struct mesh_callbacks callbacks = {rcv, snd, timeout};

PROCESS(client, "Cliente");
AUTOSTART_PROCESSES(&client);
PROCESS_THREAD(client, ev, data)
{
  PROCESS_EXITHANDLER(mesh_close(&mesh));
  PROCESS_BEGIN();
  SENSORS_ACTIVATE(button_sensor);
  
  dst.u8[0]=1;
  dst.u8[1]=0;
  mesh_open(&mesh, COMUNICATION_CHANNEL, &callbacks);
  while(1){
    PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event && data == &button_sensor); 
    packetbuf_clear();
    packetbuf_copyfrom(&mensaje, sizeof(mensaje));
    mesh_send(&mesh, &dst);
  }
  PROCESS_END();
}

