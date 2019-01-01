#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	char buffer[1024] = {'\0'};
	char str[1024] = {'\0'};
	FILE *fp;
	
	clientsock = socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_port = 3000;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	
	fp = fopen("Send.txt","r");
	
	while(fgets(buffer,sizeof(buffer),fp))
	{
		strcat(str,buffer);
	}
	
	str[strlen(str)-1] = '\0';
	
	sendto(clientsock,str,strlen(str),0,(struct sockaddr*)&server,sizeof(server));
	
}
