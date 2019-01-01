#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define PORT 3000

#include<iostream>
using namespace std;

int sock,valread;
char* hello = "Hello from client";
char buffer[1024] = {0};

class tcpsocket
{
	struct sockaddr_in serv_addr;
	
	public:
	
	int create_socket()
	{
		if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			printf("Socket creation failed");
			return -1;
		}
	
		serv_addr.sin_port = htons(PORT);
		serv_addr.sin_family = AF_INET;
	
		if((inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)) <= 0 )
		{
			printf("Invalid address");
			return -1;
		}
	
		if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
		{
			printf("Connection failed");
			return -1;
		}
	}
	
	void sayhello()
	{
		send(sock,hello,strlen(hello),0);
		printf("Hello message sent \n");
		valread = read(sock,buffer,1024);
		printf("%s\n",buffer);
	}
	
	void receivefile()
	{
		ofstream ofile("receive.txt");
		read(sock,buffer,1024);
		string(buffer);
		ofile<<buffer;
		ofile.close();
		cout<<"File received"<<endl;
	}
};

int main()
{
	tcpsocket obj;
	int val = obj.create_socket();
	obj.sayhello();	
	return 0;
}
