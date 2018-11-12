#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct lv
{
	int tot, rem, ex;
}arr[11];

void main()
{
	int ssock, csock;
	int n;
	unsigned int len;

	struct sockaddr_in server, client;
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

	if(bind(ssock, (struct sockaddr *)&server, len) == -1)
	{
		perror("Bind error\n");
		exit(-1);
	}

	if(listen(ssock, 5) == -1)
	{
		perror("Error\n");
		exit(-1);
	}

	if((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
	{
		perror("ACC Error\n");
		exit(-1);
	}

	FILE *FX;
	FX = fopen("f10.dat", "wb");
	for(int i=0;i<10;i++)
	{
		printf("Enter total, left and extra leaves for employee\n");
		scanf("%d %d %d", &arr[i].tot, &arr[i].rem, &arr[i].ex);
		fwrite(&arr[i], sizeof(struct lv), 1, FX);
	}
	fclose(FX);

	FX = fopen("f10.dat", "rb");

	while(1)
	{
		int val = 0;
		recv(csock, &n, sizeof(n), 0);
		fseek(FX, n*sizeof(struct lv), SEEK_SET);
		fread(&arr[10], sizeof(struct lv), 1, FX);
		if(arr[10].tot <= arr[10].rem + arr[10].ex)
		val = 0;
		else val = (arr[10].tot - arr[10].rem - arr[10].ex);
		send(csock, &val, sizeof(val), 0);
	}
	fclose(FX);
	close(ssock);
}