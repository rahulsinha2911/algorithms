#include<bits/stdc++.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

int main(int argc,char **argv)
{
	int csock,len;
	sockaddr_in client;
	if((csock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Client Socket not Created\n");
		exit(-1);
	}
	len=sizeof(sockaddr_in);
	client.sin_family=AF_INET;
	client.sin_port=htons(atoi(argv[2]));
	client.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&client.sin_zero,0);
	
	if(connect(csock,(sockaddr *)&client,len)==-1)
	{
		perror("Connection not Established\n");
		exit(-1);
	}
	
	while(1)
	{
		char mess[30],reply[30];
		fgets(mess,30,stdin);
		write(csock,mess,sizeof(mess));
		read(csock,reply,sizeof(reply));
		cout<<"Server : "<<reply<<endl;
		if(strncmp(reply,"Bye",3)==0)
			break;
	}
	
	close(csock);
	exit(0);
}
