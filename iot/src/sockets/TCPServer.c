#include <stdio.h>     
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXCONNECTS 10
#define PORT 3000

struct user{
  char nick[10];
  int account_type;
  char passwd[4];
};

int main(int argc, char *argv[])
{
              
    struct sockaddr_in serverAddr;
    int serverSocket;                    
    struct sockaddr_in clientAddr;
    int serviceSocket;
    int read_bytes=0;
    unsigned int serverPort;
    unsigned int len_client=0;
    struct user *new_user;


    serverPort = PORT;
    serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    memset(&serverAddr, 0, sizeof(serverAddr));   
    serverAddr.sin_family = AF_INET;                
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    serverAddr.sin_port = htons(serverPort);  
    
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, MAXCONNECTS);
    while(1)
    {
      printf("Listening clients..\n");
      len_client = sizeof(clientAddr);
      serviceSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &(len_client));
      printf("Cliente %s conectado\n", inet_ntoa(clientAddr.sin_addr));
      new_user = (struct user *)malloc(sizeof(struct user));
      read_bytes= recv(serviceSocket, new_user,sizeof(struct user) ,0);
      printf("Nuevo usuario registrado %s con cuenta %d y password %s\n", new_user->nick, new_user->account_type, new_user->passwd);
      close(serviceSocket);
    }
    
}
