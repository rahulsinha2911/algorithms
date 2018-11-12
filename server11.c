#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct dict
{
	char wrd[50], mn[50];
}arr[22];

void main()
{
	int ssock, csock;
	char wd[50];
	unsigned int len;

	struct sockaddr_in client, server;

	if((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("No socket\n");
		exit(-1);
	}	

	server.sin_family = AF_INET;
	server.sin_port = htons(30000);
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

	FILE *FX;
	FX = fopen("f11.dat", "wb");

	for(int i=0;i<5;i++)
	{
		printf("Enter word and meaning\n");
		scanf("%s %s", arr[i].wrd, arr[i].mn);
		fwrite(&arr[i], sizeof(struct dict), 1, FX);
	}	
	fclose(FX);

	FX = fopen("f11.dat", "rb");
	fseek(FX, 0, SEEK_END);
	int n = ftell(FX)/sizeof(struct dict);

	while(1)
	{
		recv(csock, wd, sizeof(wd), 0);
		char fz[20] = "ABCHORHAI";
		fseek(FX, 0, SEEK_SET);
		int ok = 0;
		for(int i=0;i<n;i++)
		{
			fread(&arr[21], sizeof(struct dict), 1, FX);
			if(!strcmp(arr[21].wrd, wd))
			{
				ok = 1;
				break;
			}	
		}	
		if(ok)
		send(csock, arr[21].mn, sizeof(arr[21].mn), 0);
		else send(csock, fz, sizeof(fz), 0);	
	}
	fclose(FX);
	close(ssock);
}	
