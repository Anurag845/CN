#include<iostream>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
using namespace std;

#define PORT 3000

class CRCr
{
	string codeword;
	string key;
	struct sockaddr_in address;
	int server_fd,addrlen,sock,opt = 1;
	char buffer1[25] = {0};
	char buffer2[25] = {0};
	
	public:
	
	CRCr()
	{
		/*cout<<"Enter received word- ";
		cin>>codeword;
		cout<<"Enter divisor- ";
		cin>>key;*/
	}
	
	int establish()
	{
		if((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0)
		{
			perror("Socket creation");
			exit(EXIT_FAILURE);
		}
		
		if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEPORT | SO_REUSEADDR,&opt,sizeof(opt)))
		{
			perror("Setsockopt");
			exit(EXIT_FAILURE);
		}
		
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_family = AF_INET;
		address.sin_port = htons(PORT);
		
		if((bind(server_fd,(struct sockaddr*)&address,sizeof(address))) < 0)
		{
			perror("Bind");
			exit(EXIT_FAILURE);
		}
		
		if(listen(server_fd,3) < 0)
		{
			perror("Listen");
			exit(EXIT_FAILURE);
		}
		
		addrlen = sizeof(address);
		
		if((sock = accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen)) < 0)
		{
			perror("Accept");
			exit(EXIT_FAILURE);
		}
		
		int val = read(sock,buffer1,sizeof(buffer1)-1);
		string codeword = buffer1;
		val = read(sock,buffer2,sizeof(buffer2)-1);
		string divisor = buffer2;
		cout<<codeword<<endl<<divisor<<endl;
		check(codeword,divisor);		
	}
	
	void check(string codeword,string key)
	{
		int n = codeword.length();
		int d = key.length();
		
		int *code = new int[n];
		int *divisor = new int[d];
		
		int i,j;
		
		for(i = 0; i < n; i++)
		{
			code[i] = codeword[i] - '0';
		}
		
		for(j = 0; j < d; j++)
		{
			divisor[j] = key[j] - '0';
		}
		
		int *temp = new int[d];
        int m = 0;
        
        for(i = 0; i < d; i++)
        {
            temp[m] = xorfun(code[i],divisor[i]);
            m++;
        }

        
        for(i = d; i < n; i++)
        {
        	for(j = 0; j < d - 1; j++)
        	{
        		temp[j] = temp[j+1];
        	}
        	temp[j] = code[i];
        	if(temp[0] == 1)
        	{
        		for(j = 0; j < d; j++)
        		{
        			temp[j] = xorfun(temp[j],divisor[j]);
        		}
        	}
        }
        
        for(i = 0; i < d - 1; i++)
        {
        	temp[i] = temp[i+1];
        }
        
        for(i = 0; i < d - 1; i++)
        {
        	cout<<temp[i];
        }
        
        cout<<endl;
	}

    int xorfun(int a,int b)
    {
    	return (a == b) ? 0 : 1; 
    }
};

int main()
{
    CRCr obj;
    int val = obj.establish();
    return 0;
}
