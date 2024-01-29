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

int sum(int a, int b)
{
	if(a&&b)
	{
		return a+b;
	}
	else if((a<0) && (b<0))
	{
		return -1;
	}

	return 0;
}


// Driver code
int main() {
	int sockfd;
	struct sockaddr_in  cliaddr,servaddr;
	
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
	

///////////////////////////////////////////////////

	//client actings as server
	int sockfd1;
	struct sockaddr_in servaddr1, cliaddr1;
		
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


	
	int n, len;
	char buffer[MAXLINE];
	char fail[]="exit";
	char message[AF_MAX];
	char *hello = &message[0];
	int len1, n1;
	char buffer1[MAXLINE];
	char message1[MAXLINE];
	
//client	
	
	while(1){
	
	printf("Type your message:");
	scanf("%s",hello);	

	sendto(sockfd, (const char *)hello, strlen(hello),
		MSG_CONFIRM,(const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Hello message sent.\n");
	if(strcmp(hello,fail)==0) 
    	{
         
	    break;
    	} 
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &servaddr,
				&len);	
			
       	buffer[n] = '\0';
	printf("After recvfrom()\n");
	printf("buffer1 is %s\n",buffer);


	
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				//MSG_WAITALL, MSG_PEEK, (struct sockaddr *) &servaddr,
				//&len);
	//buffer[n] = '\0';
	
	//printf("Server : %s\n", buffer);
	//n=(int)(*buffer);
	//n=atoi((int*)buffer);
	//printf("Length received from server is %d\n",n);
	
	
}
	
// client acting as server

	while(1){
	
		
	len1 = sizeof(cliaddr1); //len is value/result

	printf("Before recvfrom()\n");

	
	fd_set rd2;
        int hdle3 = sockfd1; //set up first source
        int hdle4 = 0; //set up second source
        int max = hdle3 > hdle4 ? hdle3 : hdle4; 
        int result1;
	

	FD_ZERO(&rd2);
	FD_SET(hdle3, &rd2);  
	FD_SET(hdle4, &rd2);
     	result1 = select(max+1, &rd2, NULL, NULL, NULL); //waiting 

     	if (FD_ISSET(hdle3, &rd2) ) {
      		printf("waiting for the message\n");
		n1 = recvfrom(sockfd1, (char *)buffer1, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &cliaddr1,
				&len1);
       		 buffer1[n1] = '\0';
	
		printf("After recvfrom()\n");
	
		printf("buffer1 is %s\n",buffer1);
		if(strcmp(buffer1,fail)==0) 
    		{
         	//printf("end the programm.");
	  	 break;
    		} 
		
	
    		}

    	 if (FD_ISSET(hdle4, &rd2)) {
		printf("waiting for the message\n");
     	 	n1 = read(0, (char*)buffer1, MAXLINE);
		buffer1[n1] = '\0';
		(char*)strcpy((char*)message1, (char*)buffer1);
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer1);
		
		sendto(sockfd1, (const char *)buffer1, strlen(buffer1),
		MSG_CONFIRM,(const struct sockaddr *) &cliaddr1,,
			sizeof(cliaddr1));	
		printf("message from keyboard sent\n.");		

		if(strcmp(message1,"exit\n")==0) 
    		{
         	//printf("end the programm.");
	  	 break;
    		} 
    		} 	
		

	}



	//char *hello1;
	//printf("waiting for the message\n");
	//n1 = recvfrom(sockfd1, (char *)buffer1, MAXLINE,
				//MSG_WAITALL,(struct sockaddr *) &cliaddr1,
				//&len1);
        //buffer1[n1] = '\0';
	
	//printf("After recvfrom()\n");
	
	//printf("buffer1 is %s\n",buffer1);
	
	



	return 0;
}

