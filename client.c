#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#define PORT "8080"
#define SERVER_ADDR "192.168.176.110"

int main(){
	
	struct addrinfo hints, *servinfo,*Servinfo;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	char Buffer[1024];
        memset(Buffer, 0, sizeof(Buffer));
	int status = getaddrinfo(SERVER_ADDR, PORT, &hints, &servinfo);

	if(status != 0){
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		
		return 1;
	}
	

	int client_fd;
	// struct addrinfo *p;
	// for(p = servinfo; p != NULL; p = p->ai_next){
	// 	client_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	// 	if(client_fd == -1){
	// 		perror("client: socket");
	// 		continue;
	// 	}

	// 	if(connect(client_fd, p->ai_addr, p->ai_addrlen) == -1){
	// 		close(client_fd);
	// 		perror("client: connect");
	// 		continue;
	// 	}

	// 	break;
	// }

	client_fd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if(client_fd!=-1)
	printf("socket made\n");
	
	if(connect(client_fd, servinfo->ai_addr, servinfo->ai_addrlen)==-1)
	 {printf("not having valid connections\n");
	   exit(0);
	   }
	 
	
	freeaddrinfo(servinfo);
	
	//server_fd = socket(Servinfo->ai_family, Servinfo->ai_socktype, Servinfo->ai_protocol);
	
	//bind(server_fd, Servinfo->ai_addr, Servinfo->ai_addrlen);

	//freeaddrinfo(Servinfo);

	// if(p == NULL){
	// 	fprintf(stderr, "client: failed to connect\n");
	// 	return 2;
	// }
        char hellotosend[1024];
        memset(hellotosend, 0, sizeof(hellotosend));
	int i;
	char hello[1024];
	memset(hello, 0, sizeof(hello));
	
        while(1)
        {printf("enter your statement\n");
          fgets(hello, sizeof(hello), stdin);
          
          
          for (i=0;i<strlen(hello)-1;i++)
          {  hellotosend[i]=hello[i];}
          
          
	if(send(client_fd, hellotosend, strlen(hellotosend), 0) == -1){
		perror("send");
		return 3;
	}
	printf("Msg sent\n");
	
	int compare=recv(client_fd, Buffer, sizeof(Buffer), 0);
	
	if (compare==-1)
		{perror("recv");
		return 5;
	}
	
	if (compare==0)
	{printf("server shutdown !!!\n"); exit(0);}
	
	   printf("%s \n", Buffer);
      }
       // else {printf("no error occured");}
	//printf("Client: Hello msg sent from client!\n");
        //send(client_fd,hello,strlen(hello),0);
	// char buffer[1024];
	// if(recv(client_fd, buffer, sizeof(buffer), 0) == -1){
	// 	perror("recv");
	// 	return 4;
	// }

	//printf("Client1: received '%s'\n", buffer);

	// const char *hello1 = "how are you?";
	// send(client_fd, hello1, strlen(hello1), 0);
	// printf("Client: Hello2 msg sent from client!\n");

	// int inp = 5;
	// for(int j = 0; j < inp; ++j){
	// 	printf("\nEnter msg: ");
	// 	char input_msg[100];
	// 	scanf("%99s", input_msg);

	// 	send(client_fd, input_msg, strlen(input_msg), 0);
	// 	printf("\nClient: Input msg sent from client!\n");
	// }

	close(client_fd);

	return 0;
}
