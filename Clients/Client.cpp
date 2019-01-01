#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fstream>
#include<arpa/inet.h>
#define PORT 3500
using namespace std;

int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";
    char buffer[1024];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout<<"\n Socket creation error \n";
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        cout<<"\nInvalid address/ Address not supported \n";
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout<<"\nConnection Failed \n";
        return -1;
    }

    send(sock , hello , strlen(hello) , 0 );
    cout<<"Hello message sent\n";

    bzero(buffer,1000);
    valread = read( sock , buffer, 1024);
    cout<<buffer<<"\n";

    string Line;
    ofstream outfile;
    outfile.open("receive.txt");
    bzero(buffer,1000);
    valread = read( sock , buffer, 1024);
    Line = string(buffer);
    outfile<<Line;
    outfile.close();
    close(sock);
    return 0;
}
