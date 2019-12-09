#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h> /* close */

char msg[20];
char receive[20];
struct sockaddr_in soc;
int socketDescriptor;

int main(int argc, char const *argv[]) {
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

  soc.sin_family = AF_INET;
  soc.sin_addr.s_addr = inet_addr("192.168.100.40");
  soc.sin_port = htons(7778);

  connect(socketDescriptor, (struct sockaddr *)&soc, sizeof(soc));
  int ok = 1;
  while(ok){
    printf(">");
    fgets(msg, sizeof(msg), stdin);
    msg[strlen(msg) - 1] = 0;
    if(!strcmp(msg, "close")) {
      ok = 0;
      printf("closing client. bye\n");
    } else {
      send(socketDescriptor, msg, strlen(msg), 0);
      recv(socketDescriptor, receive, 20, 0);
      printf("received message from server: %s\n", receive);
    }
  }
  return 0;
}
