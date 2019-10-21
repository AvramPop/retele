
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* close */


#define SUCCESS 0
#define ERROR   1

#define END_LINE 0x0
#define SERVER_PORT 1500
#define MAX_MSG 100


int main (int argc, char *argv[]) {

  int sd, newSd, cliLen;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG];


  sd = socket(AF_INET, SOCK_STREAM, 0);
   if(sd<0) {
    perror("cannot open socket ");
    return ERROR;
  }

  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = htons(SERVER_PORT);

  if(bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr))<0) {
    perror("cannot bind port ");
    return ERROR;
  }

  listen(sd,5);

  while(1) {

    printf("%s: waiting for data on port TCP %u\n",argv[0],SERVER_PORT);

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);
    if(newSd<0) {
      perror("cannot accept connection ");
      return ERROR;
    }

    memset(line,0x0,MAX_MSG);
static char rcv_msg[MAX_MSG];
uint32_t lenReceived;
uint32_t len;
    int n;
    int ok = 1;
    while(ok == 1) {

              lenReceived = 0;
              memset(rcv_msg,0x0,MAX_MSG);
              recv(newSd, &lenReceived, sizeof(uint32_t), 0);
              len = ntohl(lenReceived);
              n = recv(newSd, rcv_msg, len + 1, 0);
              rcv_msg[len] = 0;
                printf("n=%d\n", n);

              if(n<0) {
                   perror(" cannot receive data ");
                   ok = 0;
              } else if (n==0) {
                   printf(" connection closed by client\n");
                   close(newSd);
                   ok = 0;
              } else {
                printf("%s: received from %s:TCP %d : %s\n", argv[0], inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), rcv_msg);
                /* init line */
                memset(line,0x0,MAX_MSG);
              }
    }

  }

}
