#include<stdio.h>
#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 8086

using namespace std;

class Calculator()
{
	struct sockaddr_in serv_addr;
	int sock,valread;
	
	public:
	
	int create()
	{
		if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
		{
			cout<<"Socket creation failed";
			return -1;
		}
	
		memset(&serv_addr,'0',sizeof(serv_addr));
	
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(PORT);
	
		if((inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)) <= 0)
		{
			cout<<"Invalid address";
			return -1;
		}
	
		if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
		{
			cout<<"Connect failed";
			return -1;
		}
	
	}
	
	void sendinput()
	{
		float num1,num2,choice;
		char buffer[256] = {0};
		char cont;
		bzero(buffer,255);
		valread = read(sock,buffer,255);
		cout<<buffer;
		cin>>choice;
		write(sock,&choice,sizeof(float));
		bzero(buffer,255);
		valread = read(sock,buffer,255);
		cout<<buffer;
		cin>>num1;
		write(sock,&num1,sizeof(float));
		bzero(buffer,255);
		valread = read(sock,buffer,255);
		cout<<buffer;
		cin>>num2;
		write(sock,&num2,sizeof(float));
		bzero(buffer,255);
		valread = read(sock,buffer,255);
		cout<<buffer;
		cin>>cont;
		write(sock,&cont,sizeof(char));
	}

};

int main()
{
	Calculator obj;
	int val = obj.create();
	//obj.sendinput();
	return 0;
}
