#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>

void main(){
	int sock;
	unsigned int len;
	int n,a,b,add,sub,mul,div;
	char s[100];

	struct sockaddr_in client;
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket: ");
		exit(-1);
	}

	client.sin_family=AF_INET;
	client.sin_port=htons(10000);
	client.sin_addr.s_addr=INADDR_ANY;

	bzero(&client.sin_zero,0);


	len=sizeof(struct sockaddr_in);
	if((connect(sock,(struct sockaddr *)&client,len))==-1){
		perror("connect: ");
		exit(-1);
	}

	printf("Enter two numbers\n");
	scanf("%d%d",&a,&b);
	send(sock,&a,sizeof(a),0);
	send(sock,&b,sizeof(b),0);
	recv(sock,&add,sizeof(add),0);
	recv(sock,&mul,sizeof(mul),0);
	recv(sock,&sub,sizeof(sub),0);
	recv(sock,&div,sizeof(div),0);
	printf("%d %d %d %d\n",add,sub,mul,div );
	close(sock);
}
