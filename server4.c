#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int ssock,csock;
	struct sockaddr_in server,client;
	unsigned int len;

	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("Socket not created\n");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(10000);
	server.sin_addr.s_addr=INADDR_ANY;

	bzero(&server.sin_zero,0);

	len=sizeof(struct sockaddr_in);

	if(bind(ssock,(struct sockaddr*)&server,len)==-1){
		perror("Cannot bind\n");
		exit(-1);
	}


	if(listen(ssock,5)==-1){
		perror("Cannot listen\n");
		exit(-1);
	}

	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1){
		perror("Cannot accept");
		exit(-1);
	}
	int a,b;
	recv(csock,&a,sizeof(a),0);
	recv(csock,&b,sizeof(b),0);
	int add=a+b,sub=a-b,mul=a*b,div=a/b;
	send(csock,&add,sizeof(add),0);
	send(csock,&mul,sizeof(mul),0);
	send(csock,&sub,sizeof(sub),0);
	send(csock,&div,sizeof(div),0);
	close(ssock);

}