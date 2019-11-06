#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  char message[100], receivedMessage[100];
  struct sockaddr_in soc;
  soc.sin_family = AF_INET;
  soc.sin_port = htons(7778);
  soc.sin_addr.s_addr = inet_addr("172.25.14.127");
  connect(socketDescriptor, (struct sockaddr *) &soc, sizeof(soc));
  while(1){
    printf(">");
    fgets(message, 100, stdin);
    message[strlen(message) - 1] = 0;
    if(!strcmp(message, "close")) {
      printf("closing client.\n");
      send(socketDescriptor, message, strlen(message), 0);
      break;
    }
    send(socketDescriptor, message, strlen(message), 0);
    printf("sent: %s\n", message);
    recv(socketDescriptor, receivedMessage, 100, 0);
    printf("received from server: %s\n", receivedMessage);
    strcpy(receivedMessage, "");
    strcpy(message, "");
  }

  return 0;
}
