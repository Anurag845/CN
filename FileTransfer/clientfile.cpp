#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#define PORT 3000

int main(int argc, char const* argv[])
{
	int valread,sock;
	struct sockaddr_in serv_addr;
	char* hello = "Hello from client";
	char buffer[1024] = {0};
	
	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		printf("Socket creation failed");
		return -1;
	}
	
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_family = AF_INET;
	
	if((inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)) <= 0)
	{
		printf("Invalid address");
		return -1;
	}
	
	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("Connection failed");
		return -1;
	}
	
	send(sock,hello,strlen(hello),0);
	printf("Hello message sent \n");
	valread = read(sock,buffer,1024);
	printf("%s \n",buffer);
	string Line;
	ofstream ofile;
	ofile.open("receive.txt");
	bzero(buffer,1000);
	valread = read(sock,buffer,1024);
	Line = (string)buffer;
	ofile<<Line;
	ofile.close();
	close(sock);
}

