#include <netinet/ip.h>
char buf[] = "linux client c writing";
int sfd;
struct sockaddr_in soc;
main (){
  sfd=socket(AF_INET, SOCK_DGRAM, 0);

  soc.sin_family=AF_INET;
  soc.sin_port=htons(5555);
  soc.sin_addr.s_addr=inet_addr("192.168.100.40");

  sendto (sfd,buf,strlen(buf),0,&soc,sizeof(struct sockaddr_in));
}
