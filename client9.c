#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
	int sock;
	unsigned int len;
	int n;
	char wd[50];
	char ch[3] = "no";
	char ch1[3];
	struct sockaddr_in client;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("No socket\n");
		exit(-1);
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(20000);
	client.sin_addr.s_addr = INADDR_ANY;
	bzero(&client.sin_zero, 0);

	len = sizeof(struct sockaddr_in);

	if(connect(sock, (struct sockaddr *)&client, len) == -1)
	{
		perror("Can't connect\n");
		exit(-1);
	}	

	while(1)
	{
		char z;
		printf("Enter number and word\n");
		scanf("%d", &n);
		scanf("%s", wd);
		send(sock, &n, sizeof(n), 0);
		send(sock, wd, sizeof(wd), 0);
		recv(sock, &z, sizeof(z), 0);
		printf("Required char = %c\n", z);
		printf("\ndo you want to exit...press 'no'\n");
        scanf("%s",ch1);
        if(strcmp(ch,ch1))
        {
            close(sock);
            exit(0);
        }
	}
}	