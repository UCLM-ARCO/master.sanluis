#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

struct position{
  int userID;
  float x; // x coordenate 
  float y; // y coordenate
  float z; // z coordenate
  float rotation[3][3]; // 3x3 rotation matrix
};


int main(int argc, char *argv[])
{
  int serviceSocket;
  unsigned int length;
  struct hostent *server_name;
  struct sockaddr_in localAddr, clientAddr;
  struct position sensor;

  serviceSocket = socket( AF_INET, SOCK_DGRAM, 0 );
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(3000);
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  length = sizeof(clientAddr);
  bind( serviceSocket, (struct sockaddr *)&localAddr, sizeof(localAddr) );
  recvfrom(serviceSocket, &sensor, sizeof(struct position), 0, (struct sockaddr *)&clientAddr, &length );
  printf("Coche ID:%d is in position %f,%f,%f with orientation %f",sensor.userID,sensor.x, sensor.y, sensor.z, sensor.rotation[0][0]);
  return 0;
}

