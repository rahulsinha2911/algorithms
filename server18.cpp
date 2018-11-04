#include<bits/stdc++.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

int main(int argc,char **argv)
{
	int csock,ssock,len;
	sockaddr_in client,server;
	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{
		perror("Server Socket not Created\n");
		exit(-1);
	}
	len=sizeof(sockaddr_in);
	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&server.sin_zero,0);
	
	if(bind(ssock,(sockaddr *)&server,len)==-1)
	{
		perror("Binding Error\n");
		exit(-1);
	}
	if(listen(ssock,5)==-1)
	{
		perror("Channel Error\n");
		exit(-1);
	}
	
	if((csock=accept(ssock,(sockaddr *)&client,(socklen_t *)&len))==-1)
	{
		perror("Server incapable of accepting data\n");
		exit(-1);
	}
	
	while(1)
	{
		char mess[30],reply[30];
		read(csock,mess,sizeof(mess));
		cout<<"Client :  "<<mess<<endl;
		fgets(reply,30,stdin);
		write(csock,reply,sizeof(reply));
		if(strncmp(mess,"Bye",3)==0)
			break;
	}
	
	close(csock);
	close(ssock);
	exit(0);
}
