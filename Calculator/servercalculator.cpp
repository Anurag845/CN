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

class Calculator
{
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	int valread,sock,server_fd,opt = 1;
		
	public:
	
	int create_socket()
	{
		if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0)
		{
			perror("Socket creation");
			exit(EXIT_FAILURE);
		}
		
		if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)))
		{
			perror("Setsockopt");
			exit(EXIT_FAILURE);
		}
		
		address.sin_family = AF_INET;
		address.sin_port = htons(PORT);
		address.sin_addr.s_addr = INADDR_ANY;
		
		if(bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0)
		{
			perror("Bind");
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
	
	void calculate()
	{
		float num1,num2,result;
		int choice;
		char cont = 'y';
		char* menu = "1 : Addition\n2 : Subtraction\n3 : Multiplication\n4 : Division\nEnter your choice ";
		char* firstnum = "Enter 1st number ";
		char* secondnum = "Enter 2nd number ";
		char* continuity = "Do you want to continue? (y/n)";
		while(cont == 'y')
		{
			write(sock,menu,strlen(menu));
			valread = read(sock,&choice,sizeof(int));
			//cout<<choice<<endl;
			write(sock,firstnum,strlen(firstnum));
			valread = read(sock,&num1,sizeof(float));
			//cout<<num1<<endl;
			write(sock,secondnum,strlen(secondnum));
			valread = read(sock,&num2,sizeof(float));
			//cout<<num2;
			switch(choice)
			{
				case 1 : result = num1 + num2;
						 break;
				case 2 : result = num1 - num2;
						 break;
				case 3 : result = num1 * num2;
						 break;
				case 4 : result = num1/num2;
						 break;
			}
			write(sock,&result,sizeof(float));
			write(sock,continuity,strlen(continuity));
			valread = read(sock,&cont,sizeof(char));
		}
	}
	
};

int main()
{
	Calculator obj;
	int val = obj.create_socket();
	obj.calculate();
	return 0;
}
