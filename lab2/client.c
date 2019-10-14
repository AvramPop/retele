#include <netinet/ip.h>
char buf[8] = "dani";
int sfd;
struct sockaddr_in soc;
main (){
  sfd=socket(AF_INET, SOCK_DGRAM, 0);

  soc.sin_family=AF_INET;
  soc.sin_port=htons(7777);
  soc.sin_addr.s_addr=inet_addr("172.30.114.164");

  sendto (sfd,buf,strlen(buf),0,&soc,sizeof(struct sockaddr_in));
}
