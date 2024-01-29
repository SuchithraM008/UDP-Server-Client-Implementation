// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/select.h>
       
	
#define PORT	 8080
#define MAXLINE 1024
#define PORT1	 8081	
// Driver code

int main() {


	int sockfd,sockfd1;
	struct sockaddr_in servaddr, cliaddr,cliaddr1,servaddr1;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
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
	
	
	// Creating socket file descriptor
	if ( (sockfd1 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr1, 0, sizeof(servaddr1));
	memset(&cliaddr1, 0, sizeof(cliaddr1));
		
	// Filling server information
	servaddr1.sin_family = AF_INET;
	servaddr1.sin_port = htons(PORT1);
	servaddr1.sin_addr.s_addr = INADDR_ANY;
	
	
	

	int len,n,len1;
	char buffer[MAXLINE];
	char message[MAXLINE];
	char fail[]="end";

 
	len = sizeof(cliaddr); 
	len1 = sizeof(servaddr1);
	
	while(1){

	fd_set rd1;
        int hdle1 = sockfd; 
        int hdle2 = 0; 
	int max = hdle1 > hdle2 ? hdle1 : hdle2; 
        int result;
	
	FD_ZERO(&rd1);
	FD_SET(hdle1, &rd1);  
	FD_SET(hdle2, &rd1);
	
     	result = select(max+1, &rd1, NULL, NULL, NULL);

     	if (FD_ISSET(hdle1, &rd1) ) {
      	
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &cliaddr,
				&len);
       		 buffer[n] = '\0';
		//(char*)strcpy((char*)message, (char*)buffer);
	
		
		printf("hello");
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer);	
		if(strcmp(buffer,"end\n")==0) 
    		{
	  	 break;
    		} 
		printf("buffer is %s\n",buffer);
	
    		}

    	 if (FD_ISSET(hdle2, &rd1)) {
		
     	 	n = read(0, (char*)buffer, MAXLINE);
		buffer[n] = '\0';
		//(char*)strcpy((char*)message, (char*)buffer);
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer);
		sendto(sockfd1,(const char *)buffer, strlen(buffer),
		MSG_CONFIRM,(const struct sockaddr *) &servaddr1,
			sizeof(servaddr1));
		
		if(strcmp(buffer,"end\n")==0) 
    		{
	  	 break;
    		} 
		printf("buffer is %s\n",buffer);
    		} 
	
	 



	


}

	return 0;
}

