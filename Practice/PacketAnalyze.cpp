#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;

int main()
{
	int ch;
	char choice = 'y';
	string sr_no,time,source,destination,len,info,protocol,protocolChoice;
	while(choice == 'y')
	{
		ifstream ifile("data.csv");
		int count = -1;
		int i = 0;
		cout<<"Enter 1 for Ethernet"<<endl;
		cout<<"Enter 2 for TCP"<<endl;
		cout<<"Enter 3 for UDP"<<endl;
		cout<<"Enter 4 for IP"<<endl;
		cin>>ch;
		switch(ch) {
			case 1: protocolChoice = "ARP";
					break;
			case 2: protocolChoice = "TCP";
					break;
			case 3: protocolChoice = "UDP";
					break;
			case 4: protocolChoice = "ICMPv6";
					break;
			default:protocolChoice = "ARP";
					break;
		}
		
		while(ifile.good())
		{
			getline(ifile,sr_no,',');
			getline(ifile,time,',');
			getline(ifile,source,',');
			getline(ifile,destination,',');
			getline(ifile,protocol,',');
			getline(ifile,len,',');
			getline(ifile,info,'\n');
			
			protocol = string(protocol,1,protocol.length()-2);
			//cout<<protocol<<"  "<<protocolChoice<<endl;
			
			if(protocol == protocolChoice || protocol == "Protocol")
			{
				cout<<setw(4)<<left<<i++;
				cout<<setw(12)<<left<<string(time,1,time.length()-2);
				cout<<setw(30)<<left<<string(source,1,source.length()-2);
				cout<<setw(30)<<left<<string(destination,1,destination.length()-2);
				cout<<setw(8)<<left<<protocol;
				cout<<setw(8)<<left<<string(len,1,len.length()-2);
				cout<<string(info,1,info.length()-2)<<endl;
				count++;
			}
			
		}
		cout<<"Count of "<<protocolChoice<<" packets is "<<count<<endl;
		cout<<"Do you want to continue?"<<endl;
		cin>>choice;
	}
	return 0;
}
