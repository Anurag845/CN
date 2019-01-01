#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
using namespace std;

#define PORT 3000

class CRCs
{
    string data;
    string key;
    char* codeword = NULL;
    char* divisor = NULL;
    struct sockaddr_in serv_addr;
    int valread,sock;
    
    public:
    
    CRCs()
    {
        cout<<"Enter data word :- ";
        cin>>data;
        cout<<"Enter divisor :- ";
        cin>>key;
    }
   
    
    int establish()
    {
    	if((sock = socket(AF_INET,SOCK_STREAM,0)) < 0)
    	{
    		cout<<"Socket creation failed"<<endl;
    		return -1;
    	}
    	
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(PORT);
    	
    	if((inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)) <= 0)
    	{
    		cout<<"Invalid address"<<endl;
    		return -1;
    	}
    	
    	if((connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0)
    	{
    		cout<<"Connection failed"<<endl;
    		return -1;
    	}
    }
   
    
    void divide()
    {
        int k = data.length();
        int d = key.length();
        int n = k + d -1;
        int i,j;
        
        int *dataword = new int[n];
        
        for(i = 0; i < k; i++)
        {
            dataword[i] = data[i] - '0';
        }
        
        int *div = new int[d];
        
        for(i = 0; i < d; i++)
        {
            div[i] = key[i] - '0';
        }
        
        for(i = k; i < n; i++)
        {
            dataword[i] = 0;
        }
        
        int *temp = new int[d];
        int m = 0;
        
        for(i = 0; i < d; i++)
        {
            temp[m] = xorfun(dataword[i],div[i]);
            m++;
        }

        
        for(i = d; i < n; i++)
        {
        	for(j = 0; j < d - 1; j++)
        	{
        		temp[j] = temp[j+1];
        	}
        	temp[j] = dataword[i];
        	if(temp[0] == 1)
        	{
        		for(j = 0; j < d; j++)
        		{
        			temp[j] = xorfun(temp[j],div[j]);
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
        
        for(i = k; i < n; i++)
        {
        	dataword[i] = temp[i-k];
        }
        
        string dataw = "";
        string divw = "";
        
        for(i = 0; i < n; i++)
        {
        	dataw += dataword[i] + '0';
        }
        
        cout<<div<<" divisor int array"<<endl;
        
        for(i = 0; i < d; i++)
        {
        	cout<<div[i]<<" ";
        	divw += div[i] + '0';
        }
        
        codeword = &dataw[0];
        divisor = &divw[0];
        
        cout<<endl;
    }
    
    void send()
    {
    	write(sock,codeword,strlen(codeword));
    	cout<<"Codeword sent"<<endl;
    	write(sock,divisor,strlen(divisor));
    	cout<<"Divisor sent"<<endl;
    }
    
    int xorfun(int a,int b)
    {
    	return (a == b) ? 0 : 1; 
    }
};

int main()
{
    CRCs obj;
    obj.divide();
    int val = obj.establish();
    obj.send();
    return 0;
}
