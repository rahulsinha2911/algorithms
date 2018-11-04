#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
void main()
{
int sock;
int a,b,c,i;
unsigned int len;
char ch[3]="no";
char ch1[3];
struct sockaddr_in client;
if( (sock=socket(AF_INET,SOCK_STREAM,0))==-1 )
{
// client socket is created..
perror("socket: ");
exit(-1);
}
client.sin_family=AF_INET;
client.sin_port=htons(10000);
client.sin_addr.s_addr=INADDR_ANY;
bzero(&client.sin_zero,0);
len=sizeof(struct sockaddr_in);
if( (connect(sock,(struct sockaddr *)&client,len))==-1)
{
//conneting to client
//Date of Submission-> 06-Aug-2018
perror("connect: ");
exit(-1);
}
while(1)
{
printf("Server--");
printf("Enter A Number :\n");
scanf("%d",&a);
send(sock,&a,sizeof(a),0);
printf("\nServer: ");
for(b=0;b<a;b++)
{
recv(sock,&c,sizeof(c),0);
printf("%d ",c);
}
printf("\nServer: Do you want to exit...press 'no' else press any key\n");
scanf("%s",ch1);
if((i=strcmp(ch,ch1))==0)
{
printf("\nServer: GOT it!\n");
close(sock);
exit(0);
}
}
}
