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
    int sock;      // client socket discriptor
    int i;
    char c[30], z[30];
    unsigned int len;

    struct sockaddr_in client;
    if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
    {  // client socket is created..
        perror("socket: ");
        exit(-1);
    }

    client.sin_family=AF_INET;
    client.sin_port=htons(10000);        // initializing  socket  parameters
    client.sin_addr.s_addr=INADDR_ANY;
    //inet_addr("127.0.0.1");
    bzero(&client.sin_zero,0); //appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'..


    len=sizeof(struct sockaddr_in);
    if((connect(sock,(struct sockaddr *)&client,len))==-1)
    {  //conneting to client
        perror("connect: ");
        exit(-1);
    }
    while(1)
    {
        printf("enter required password:\n");
        scanf("%s",c);

        send(sock,c,sizeof(c),0);
      // sending data back to client...
      char t[10];
        recv(sock,&i,sizeof(i),0);
        if(i == 1)
        {
            strcpy(c,"Hi");
            send(sock,c,sizeof(c),0);
            recv(sock,z,sizeof(z),0);
            printf("answer is %s\nPress any key to close\n",z);
            scanf("%s",t);
            close(sock);
            exit(0);
        }
        else                           // receiving data from client
        {
            recv(sock,z,sizeof(z),0);
            printf("%s\n", z);
            close(sock);
            exit(0);
        }
    }
}
