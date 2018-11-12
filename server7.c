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
	int ssock, csock;
	int n;
	int arr[1001];
	unsigned int len;

	struct sockaddr_in client, server;

	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("No socket\n");
		exit(-1);
	}	

	server.sin_family = AF_INET;
	server.sin_port = htons(20000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 0);

	len = sizeof(struct sockaddr_in);

	if((bind(ssock, (struct sockaddr *)&server, len)) == -1)
	{
		perror("Cannot bind\n");
		exit(-1);
	}	

	if(listen(ssock, 5) == -1)
	{
		perror("Cannot listen\n");
		exit(-1);
	}

	if((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
	{
		perror("Cannot accept\n");
		exit(-1);
	}

	while(1)
	{
		recv(csock, &n, sizeof(n), 0);
		int x = n;
		for(int i=2;i<=n;i++)
		{
			int ct = 0;
			while(!(x % i))
			{
				ct++;
				x /= i;
			}	
			arr[i] = ct;
		}	
		send(csock, arr, sizeof(arr), 0);
		printf("Data sent\n");
	}
	close(ssock);
}