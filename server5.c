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
	int ssock, csock;
	int n;
	unsigned int len;
	char pat[101][101]; 

	struct sockaddr_in server, client;
	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket not present\n");
		exit(-1);
	}	

	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;

	bzero(&server.sin_zero, 0);

	len = sizeof(struct sockaddr_in);
	
	if((bind(ssock, (struct sockaddr *)&server, len)) == -1)
	{
		perror("Can't bind\n");
		exit(-1);
	}	

	if((listen(ssock, 5)) == -1)
	{
		perror("Can't listen\n");
		exit(-1);
	}	

	if((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
	{
		perror("Not accepting\n");
		exit(-1);
	}	

	while(1)
	{
		recv(csock, &n, sizeof(n), 0);
		memset(pat, ' ', sizeof(pat));
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<i;j++)
			pat[i][j] = ' ';	
			for(int j=0;j<(2*(n-i)-1);j++)
			{
				if(j & 1)
				pat[i][i+j] = ' ';
				else pat[i][i+j] = '*';	
			}	
			for(int j=2*n-i-1;j<n;j++)
			pat[i][j] = ' ';
			pat[i][2*n] = '\0'; 	
		}
		send(csock, pat, sizeof(pat), 0);
		printf("Sent\n");
	}
	close(ssock);
}