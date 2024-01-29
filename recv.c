// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
	
#define PORT	 8081
#define MAXLINE 1024
	
// Driver code

int UDPRecv(int socketfd,char* buffer);

int main() {
	int sockfd;
	struct sockaddr_in servaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	


	int n,out;
	char message[1000];
	char *hello = "Hello world";
	
	printf("Type your message:   ");
	//scanf("%s",hello);
	//printf("message %s\n",hello);
	out = UDPRecv(0,hello);
	
	printf("recv function returns: %d\n",out);

	return 0;
}


int UDPRecv(int socketfd,char* buffer){
	int n;
	n = read(socketfd, (char*) buffer, MAXLINE);
	//if(n<0)
	//{
	//	fprintf(stderr, "Value of errno: %d\n", errno);
		//perror("Error printed by perror");
		//fprintf(stderr, "Error opening file: %s\n", strerror( errno ));
	//}
        return n;
	}
