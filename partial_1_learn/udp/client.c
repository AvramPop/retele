#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

int main (){
  struct sockaddr_in soc;
  int sfd;
  sfd = socket(AF_INET, SOCK_DGRAM, 0);
  char buf[100];
  char received[100];

  soc.sin_family = AF_INET;
  soc.sin_port = htons(5555);
  soc.sin_addr.s_addr = inet_addr("192.168.100.13");
  while(1){
    printf(">");
    fgets(buf, 100, stdin);
    buf[strlen(buf) - 1] = 0;
    if(!strcmp(buf, "close")){
      printf("closing client\n");
      sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*) &soc, sizeof(soc));
      break;
    }
    sendto(sfd, buf, strlen(buf), 0, (struct sockaddr*) &soc, sizeof(soc));
    recvfrom(sfd, received, 100, 0, (struct sockaddr*) &soc, sizeof(soc));
    printf("client received: %s\n", received);
    strcpy(received, "");
  }
  return 0;
}
