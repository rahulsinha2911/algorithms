#include<bits/stdc++.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

char words[30][30];
void getwords()
{
	for(int i=0;i<6;i++)
		fgets(words[i],30,stdin);
}

int main()
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
	client.sin_port=htons(1500);
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	bzero(&client.sin_zero,0);
	
	if(connect(csock,(sockaddr *)&client,len)==-1)
	{
		perror("Connection not Established\n");
		exit(-1);
	}
	
	getwords();
	
	while(1)
	{
		int n,t;
		char ans[50],s[30];
		n=rand()%8;
		strcpy(s,words[n]);
		write(csock,s,sizeof(s));
		read(csock,ans,sizeof(ans));
		cout<<endl<<ans;
		cout<<endl<<"Enter 1 to exit  :  ";
		cin>>t;
		if(t==1)
			break;
	}
	close(csock);
	exit(0);
}
