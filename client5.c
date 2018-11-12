#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

void main()
{
	int sock;
	int n;
	char pat[101][101];
	char ch[3] = "no";
	char ch1[3];
	unsigned int len;

	struct sockaddr_in client;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket not given\n");
		exit(-1);
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(10000);
	client.sin_addr.s_addr = INADDR_ANY;
	bzero(&client.sin_zero, 0);

	len = sizeof(struct sockaddr_in);

	if((connect(sock, (struct sockaddr *)&client, len)) == -1)
	{
		perror("Can't connect\n");
		exit(-1);
	}

	while(1)
	{
		printf("Enter number for pattern\n");
		scanf("%d", &n);
		send(sock, &n, sizeof(n), 0);
		recv(sock, pat, sizeof(pat), 0);
		for(int i=0;i<n;i++)
		printf("%s\n", pat[i]);
		printf("\ndo you want to exit...press 'no'\n");
        scanf("%s",ch1);
        if(strcmp(ch,ch1))
        {
            close(sock);
            exit(0);
        }
   	}
}