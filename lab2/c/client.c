#include <netinet/ip.h>
char buf[] = "merge";
int sfd;
struct sockaddr_in soc;
main (){
  sfd=socket(AF_INET, SOCK_DGRAM, 0);

  soc.sin_family=AF_INET;
  soc.sin_port=htons(7777);
  soc.sin_addr.s_addr=inet_addr("10.0.2.15");

  sendto (sfd,buf,strlen(buf),0,&soc,sizeof(struct sockaddr_in));
}
