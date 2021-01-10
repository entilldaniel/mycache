#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "proto/handler.h"

#define DEFAULT_PORT 4488

void *connection_handler(void *);


int main(int argc, char *argv[]) {
  int socket_desc, new_socket, c, portno, *new_sock;
  struct sockaddr_in server, client;
  char *message;

  if (argc < 2) {
	printf("Using default port %d\n", DEFAULT_PORT);
	portno = DEFAULT_PORT;
  } else {
	portno = atoi(argv[1]);
  }

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc < 0) {
	puts("Could not create socket.");
	exit(1);
  }

  //Prepare socket
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(portno);

  if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
	puts("bind failed");
	exit(1);
  }
  puts("bind done.");

  listen(socket_desc, 3);
  puts("Listening for incoming connections.");

  c = sizeof(struct sockaddr_in);
  while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*)&c))) {
	puts("Connection accepted.");

	message = "Connection accepted.";
	write(new_socket, message, strlen(message));
	
	pthread_t sniffer_thread;
	new_sock = malloc(1);
	*new_sock = new_socket;

	if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) > 0) {
	  perror("Could not create thread.");
	  exit(2);
	}

	pthread_join(sniffer_thread, NULL);
  }

  if (new_socket < 0) {
	perror("accept failed.");
	exit(1);
  }
  
  puts("Exiting normally");
  close(socket_desc);
  return 0;
}

void *connection_handler(void* socket_desc) {
  int sock = *(int*)socket_desc;
  int read_size;
  char *message, client_message[2048];
  
  while((read_size = recv(sock, client_message, sizeof(client_message), 0)) > 0 ) {
	int result = handle(client_message);
	char str[10];
	sprintf(str, "%d", result);
  	write(sock , str, strlen(str));
  }
  if(read_size == 0) {
  	puts("Client disconnected");
  
  } else if (read_size = -1) {
  	perror("Recv failed.");
  }
  fflush(stdout);
  free(socket_desc);
  
  return 0;
}


  









