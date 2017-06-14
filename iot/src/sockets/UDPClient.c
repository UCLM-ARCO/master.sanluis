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
  struct hostent *server_name;
  struct sockaddr_in localAddr, serverAddr;
  struct SensorUpdate mypos;


  mypos.SensorID=10;
  mypos.x=23;
  mypos.y=21;
  mypos.z=0;
  mypos.rotation[0][0]=1;

  serviceSocket = socket( AF_INET, SOCK_DGRAM, 0 );
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = 0;
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  server_name = gethostbyname("localhost");
  memset(&serverAddr, 0, sizeof(serverAddr));
  memcpy(&serverAddr.sin_addr, server_name->h_addr_list[0], server_name->h_length);
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(3000);
   
  memset( &( serverAddr.sin_zero), '\0', 8 );
  length = sizeof( struct sockaddr_in );
  bind( serviceSocket, (struct sockaddr *)&localAddr, length );
  sendto(serviceSocket, &mypos, sizeof(struct SensorUpdate), 0, (struct sockaddr *)&serverAddr, length );
  return 0;
}
