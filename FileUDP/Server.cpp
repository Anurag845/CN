#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock;
	char buffer[1024] = {0};
	FILE *fp;
	
	serversock = socket(AF_INET,SOCK_DGRAM,0);
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = 3000;
	server.sin_family = AF_INET;
	
	bind(serversock,(struct sockaddr*)&server,sizeof(server));
	
	unsigned int n = sizeof(client);
	
	recvfrom(serversock,buffer,sizeof(buffer),0,(struct sockaddr*)&client,&n);
	
	fp = fopen("new.txt","w");
	fprintf(fp,"%s",buffer);
	
	cout<<"File received successfully"<<endl;
	
}
