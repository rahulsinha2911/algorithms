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
	int arr[1001];
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
		printf("Enter n\n");
		scanf("%d", &n);
		int x = n;
		send(sock, &x, sizeof(x), 0);
		recv(sock, arr, sizeof(arr), 0);
		for(int i=2;i<=n;i++)
		{
			if(arr[i])
			printf("%d^%d ", i, arr[i]);	
		}	
		printf("\n");
		printf("\ndo you want to exit...press 'no'\n");
        scanf("%s",ch1);
        if(strcmp(ch,ch1))
        {
            close(sock);
            exit(0);
        }
	}
}