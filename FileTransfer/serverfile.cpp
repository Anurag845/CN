#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
#define PORT 3000

int valread,sock,server_fd,opt = 0;
char* hello = "Hello from server";
char buffer[1024] = {0};

class tcpsocket 
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
	public:
	
	int create_socket() 
	{
		if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0)
		{
			perror("Socket creation failure");
			exit(EXIT_FAILURE);
		}
	
		if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEPORT | SO_REUSEADDR,&opt,sizeof(opt)))
		{
			perror("Setsockopt");
			exit(EXIT_FAILURE);
		}
	
		address.sin_family = AF_INET;
		address.sin_port = htons(PORT);
		address.sin_addr.s_addr = INADDR_ANY;
	
		if((bind(server_fd,(struct sockaddr*)&address,sizeof(address))) < 0)
		{
			perror("Bind failed");
			exit(EXIT_FAILURE);
		}
	
		if(listen(server_fd,3) < 0)
		{
			perror("Listen");
			exit(EXIT_FAILURE);
		}
	
		if((sock = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0)
		{
			perror("Accept");
			exit(EXIT_FAILURE);
		}
	}	
	
	void sayhello()
	{
		valread = read(sock,buffer,1024);
		cout<<buffer<<endl;
		send(sock,hello,strlen(hello),0);
		cout<<"Hello message sent \n";
	}
	
	void sendfile()
	{
		ifstream ifile("send.txt");
		string content = " ";
		while(!ifile.eof())
		{
			content += ifile.get();
		}
		
		content.erase(content.end()-1);
		bzero(buffer,1000);
		strcpy(buffer,content.c_str());
		send(sock,buffer,strlen(buffer),0);
		ifile.close();
		cout<<"File sent successfully"<<endl;
	}
};

int main()
{
	tcpsocket obj;
	int val = obj.create_socket();
	obj.sayhello();
	obj.sendfile();
	return 0;
}
