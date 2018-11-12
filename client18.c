#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
  int ssock;
  size_t len = sizeof(struct sockaddr_in);

  if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("socket not created\n");
    return -1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY; //2130706433l
  bzero((char*)&server.sin_zero, sizeof(server.sin_zero));

  if(connect(ssock, (struct sockaddr* )&server, len) < 0){
    printf("connect error\n");
    return -1;
  }
  printf("1. fetch\t\t2. Broadcast\n");
  while(1){
    int status;
    printf("choice? ");
    scanf("%d", &status);
    size_t len = 1024;
    char *buffer = (char*)malloc(1024);

    send(ssock, &status, sizeof(int), 0);
    if(status==1){
      for(int i=0; i<50; i++) printf("\n\n");
      int buffers_num;
      recv(ssock, &buffers_num, sizeof(int), 0);
      while(buffers_num--){
        recv(ssock, buffer, len, 0);
        printf("%s\n", buffer);
      }
    }
    else{
      printf("Enter message: ");
      scanf("%s", buffer);
      send(ssock, buffer, 1024, 0);
    }

    free(buffer);
  }

}
