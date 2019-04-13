#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    	int server_fd, new_socket, valread;
    	struct sockaddr_in address;
    	int opt = 1;
    	int addrlen = sizeof(address);
    	char buffer[1024] = {0};
    	char *msg1 = "transaksi berhasil";
    	char *msg2 = "transaksi gagal";

    	key_t key = 1234;
    	int *value;

    	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    	value = shmat(shmid, NULL, 0);

    	*value=0;

    	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        	perror("socket failed");
        	exit(EXIT_FAILURE);
    	}

    	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        	perror("setsockopt");
        	exit(EXIT_FAILURE);
    	}

    	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons( PORT );

    	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        	perror("bind failed");
        	exit(EXIT_FAILURE);
    	}

    	if (listen(server_fd, 3) < 0) {
        	perror("listen");
        	exit(EXIT_FAILURE);
    	}

    	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        	perror("accept");
        	exit(EXIT_FAILURE);
    	}

    	while(strcmp(buffer, "tutup"))
    	{
        	memset(buffer, 0, sizeof(buffer));
        	valread = read( new_socket , buffer, 1024);

  		if(!strcmp(buffer, "beli"))
  		{
      			if(*value>0)
      			{
    				*value-=1;
    				send(new_socket , msg1 , strlen(msg1) , 0 );
      			}
      			else
      			{
    				send(new_socket , msg2 , strlen(msg2) , 0 );
      			}
  		}
    	}
    	return 0;
}
