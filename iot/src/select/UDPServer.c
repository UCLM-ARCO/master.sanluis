#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
struct SensorUpdate{
  int SensorID;
  float x; // x coordenate 
  float y; // y coordenate
  float z; // z coordenate
  float rotation[3][3]; // 3x3 rotation matrix
};

int main(int argc, char *argv[])
{
  int serviceSocket;
  unsigned int length;
  struct sockaddr_in localAddr, clientAddr;

  struct SensorUpdate sensor;

  serviceSocket = socket( AF_INET, SOCK_DGRAM, 0 );
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(3000);
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  length = sizeof(clientAddr);
  bind( serviceSocket, (struct sockaddr *)&localAddr, sizeof(localAddr) );

  fd_set readSet;
  FD_ZERO(&readSet);
  FD_SET(serviceSocket,&readSet);

  while(select(serviceSocket+1, &readSet,0,0,NULL)){
    if (FD_ISSET(serviceSocket,&readSet)){
      recvfrom(serviceSocket, &sensor, sizeof(struct SensorUpdate), 0, (struct sockaddr *)&clientAddr, &length );
      fprintf(stderr,"Sensor ID:%d is in SensorUpdate %f,%f,%f with orientation %f\n",sensor.SensorID,sensor.x, sensor.y, sensor.z, sensor.rotation[0][0]);

    }
  }
  return 0;
}

