#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <vector>
std::vector<char*> buffers;

void* handleclient(void* arg){
  int sock = *((int*) arg);
  while(1){
      int status;
      recv(sock, &status, sizeof(int), 0);
      if(status==1){
        int num=buffers.size();
        send(sock, &num, sizeof(int), 0);
        for(int i=0; i<buffers.size(); i++) send(sock, buffers[i], 1024, 0);
      }

      else{
        char *buffer = (char*)malloc(1024);
        recv(sock, buffer, 1024, 0);
        buffers.push_back(buffer);
      }
  }
}

int main(){
  int ssock, csock;
  unsigned int len = sizeof(struct sockaddr_in);

  if((ssock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("socket not created\n");
    return -1;
  }

  sockaddr_in server, client;
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero((char*)&server.sin_zero, sizeof(server.sin_zero));

  if(bind(ssock, (struct sockaddr*)&server, len) < 0){
    printf("Bind Error\n");
    return -1;
  }

  std::vector<pthread_t> threads;
  while(1){
    listen(ssock, 5);
    if((csock = accept(ssock, (struct sockaddr*)&client, &len)) < 0){
      printf("connect error\n");
      return -1;
    }

    pthread_t newThread;
    threads.push_back(newThread);
    pthread_create(&threads.back(), NULL, handleclient, (void*)&csock);
  }
}
