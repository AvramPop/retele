#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>

void killChild(int sig)
{
	wait(0);
}

void serveClient(int port){
	int s=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in server,client;

	server.sin_family=AF_INET;
	server.sin_port=htons(port);
	server.sin_addr.s_addr=INADDR_ANY;

	bind(s,(struct sockaddr*) &server, sizeof(server));
	int x,y;
	int len=sizeof(client);
	while (1) {

		recvfrom(s, &x, sizeof(x), 0, (struct sockaddr*) &client, &len);
		printf("x = %d, ip = %s\n", ntohl(x), inet_ntoa(client.sin_addr));
		recvfrom(s, &y, sizeof(y), 0, (struct sockaddr*) &client, &len);
		printf("y = %d, ip = %s, port=%d\n", ntohl(y), inet_ntoa(client.sin_addr),port);

		x = ntohl(x);
		y = ntohl(y);
		int ans=0;
		printf("%d %d\n",x,y);
		if(x==1 && y==1)
		{
			ans=1;
		}
		ans = htonl(ans);
		sendto(s, &ans, sizeof(ans), 0, (struct sockaddr*) &client, sizeof(client));
		if(x==1 && y==1)
		{
			break;
		}
	}

	printf("Over with ip =%s\n", inet_ntoa(client.sin_addr));
}

int main()
{
	signal(SIGCHLD,killChild);
	int gatekeeperPort=7777;
	int clientPort=2001;

	struct sockaddr_in gatekeeperServer,newClient;
	int s;
	gatekeeperServer.sin_family=AF_INET;
	gatekeeperServer.sin_port=htons(gatekeeperPort);
	gatekeeperServer.sin_addr.s_addr=INADDR_ANY;

	s=socket(AF_INET,SOCK_DGRAM, 0);

	bind(s, (struct sockaddr*) &gatekeeperServer,sizeof(gatekeeperServer));
	int req;
	int len=sizeof(newClient);
	printf("Listen...\n");
	while(1)
	{
		printf("asd\n");		
		recvfrom(s, &req, sizeof(req), 0, (struct sockaddr*) &newClient , &len);
		req=ntohl(req);
		printf("%d\n",req);
		if(req==1)
		{
			printf("New Client\n");
			++clientPort;
			if(fork()==0)
			{
				int port = htonl(clientPort);
				sendto(s,&port,sizeof(port),0,(struct sockaddr*) &newClient,sizeof(newClient));
				serveClient(clientPort);
				exit(0);
			}
		}
	}
	return 0;
}
