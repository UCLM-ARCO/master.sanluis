#include <stdio.h>     
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#define MAXCONNECTS 10
#define PORT 3000
#define PREMIUM 1

struct user{
  char nick[10];
  int account_type;
  char passwd[4];
};

int main(int argc, char *argv[])
{
              
    struct sockaddr_in serverAddr;
    struct hostent     *server_name;
    int serviceSocket;
    unsigned int serverPort;
    struct user myData;
    int send_bytes=0;
    int len_server=0;
   
    strncpy(myData.nick,"Quijote",sizeof("Quijote"));
    myData.account_type = PREMIUM;
     strncpy(myData.passwd,"123",sizeof("123"));

    serverPort = PORT;
    serviceSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    server_name = gethostbyname("161.67.48.189");
    memset(&serverAddr, 0, sizeof(serverAddr));
    memcpy(&serverAddr.sin_addr, server_name->h_addr_list[0], server_name->h_length);
    serverAddr.sin_family = AF_INET;                
    serverAddr.sin_port = htons(serverPort);  
    
    len_server = sizeof(serverAddr);
    printf("Connecting to server..");
    connect(serviceSocket,(struct sockaddr *) &serverAddr,(socklen_t)len_server);
    printf("Done!\n Sending credentials.. %s\n", myData.nick);
    send_bytes = send(serviceSocket, &myData, sizeof(myData),0);
    printf("Done! %d\n",send_bytes);
    close(serviceSocket);
    return 0;    
}
