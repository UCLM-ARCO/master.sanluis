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
  struct position otherplayer;
  struct position player;

  otherplayer.userID=9;
  otherplayer.x=10;
  otherplayer.y=10;
  otherplayer.z=0;
  otherplayer.rotation[0][0]=2;

  serviceSocket = socket( AF_INET, SOCK_DGRAM, 0 );
  localAddr.sin_family = AF_INET;
  localAddr.sin_port = htons(3000);
  localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  length = sizeof(clientAddr);
  bind( serviceSocket, (struct sockaddr *)&localAddr, sizeof(localAddr) );
  recvfrom(serviceSocket, &player, sizeof(struct position), 0, (struct sockaddr *)&clientAddr, &length );
  printf("Player ID:%d is in position %f,%f,%f with orientation %f",player.userID,player.x, player.y, player.z, player.rotation[0][0]);
  sendto(serviceSocket, &otherplayer, sizeof(struct position), 0, (struct sockaddr *)&clientAddr, length );
  return 0;
}

