// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT	 8080
#define MAXLINE 1024
#define PORT1	 8081


// Driver code
int main() {
	int sockfd,sockfd1;
	struct sockaddr_in  cliaddr,servaddr,servaddr1, cliaddr1;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	// Creating socket file descriptor
	if ( (sockfd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr1, 0, sizeof(servaddr1));
	memset(&cliaddr1, 0, sizeof(cliaddr1));
		
	// Filling server information
	servaddr1.sin_family = AF_INET; // IPv4
	servaddr1.sin_addr.s_addr = INADDR_ANY;
	servaddr1.sin_port = htons(PORT1);
		
	// Bind the socket with the server address
	if ( bind(sockfd1, (const struct sockaddr *)&servaddr1,
			sizeof(servaddr1)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	
	int n,len,len1;
	char buffer[MAXLINE];
	char fail[]="end";

	len1 = sizeof(cliaddr1);
	len = sizeof(servaddr); 

	
	while(1){
	fd_set rd2;
        int hdle3 = sockfd1; 
        int hdle4 = 0;
	 int max = hdle3 > hdle4 ? hdle3 : hdle4; 
	
        int result1;
	

	FD_ZERO(&rd2);
	FD_SET(hdle3, &rd2);  
	FD_SET(hdle4, &rd2);
     	result1 = select(max+1, &rd2, NULL, NULL, NULL); 

     	if (FD_ISSET(hdle3, &rd2) ) {
      		
		n = recvfrom(sockfd1, (char *)buffer, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &cliaddr1,
				&len1);
       		 buffer[n] = '\0';
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer);
		
		
		if(strcmp(buffer,"end\n")==0) 
    		{
	  	 break;
    		} 
		
		printf("buffer is %s\n",buffer);
    		}

    	 if (FD_ISSET(hdle4, &rd2)) {
	
     	 	n = read(0, (char*)buffer, MAXLINE);
		buffer[n] = '\0';
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer);
		sendto(sockfd, (const char *)buffer, strlen(buffer),
		MSG_CONFIRM,(const struct sockaddr *) &servaddr,
			sizeof(servaddr));
		
    		
		
		if(strcmp(buffer,"end\n")==0) 
    		{
	  	 break;
    		} 
		printf("buffer is %s\n",buffer);
		}
}
	

	return 0;
}

