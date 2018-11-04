#include<bits/stdc++.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

void build(map<char *,char *> &mp)
{
	for(int i=0;i<4;i++)
	{
		char word[30],mean[50];
		cout<<endl<<"Enter Question  :  ";
		fgets(word,30,stdin);
		cout<<"\nEnter its Answer  :  ";
		fgets(mean,50,stdin);
		mp[word]=mean;
	}
}

int main()
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
	server.sin_port=htons(1500);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
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
	
	map<char *,char *> mp;
	build(mp);
	
	if((csock=accept(ssock,(sockaddr *)&client,(socklen_t *)&len))==-1)
	{
		perror("Server incapable of accepting data\n");
		exit(-1);
	}
	
	while(1)
	{
		char w[30],ans[50];
		read(csock,w,sizeof(w));
		if(mp.find(w)!=mp.end())
			strcpy(ans,mp[w]);
		else 
		{
			strcpy(ans,"Try Again");
		}
		write(csock,ans,sizeof(ans));
	}
	close(csock);
	close(ssock);
	exit(0);
}
