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


	int sockfd;
	struct sockaddr_in servaddr, cliaddr;
		
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
	

///////////////////////////////////////////////////////	

	//SERVER ACTING AS CLIENT📎️
	int sockfd1;
	struct sockaddr_in  cliaddr1,servaddr1;
	
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
	
	
	

	int len, n;
	char buffer[MAXLINE];
	char message[MAXLINE];
	char *hello;
	//char buffer1[MAXLINE];
	//char message1[AF_MAX];
	char *hello1 = &message[0];
	char fail[]="exit";
	int len1,n1

 	//char *end = "client requested to exit";
	len = sizeof(cliaddr); //len is value/result
	printf("Before recvfrom()\n");

//server	
	while(1){
	
	fd_set rd1;
        int hdle1 = sockfd; //set up first source
        int hdle2 = 0; //set up second source
        int max = hdle1 > hdle2 ? hdle1 : hdle2; 
        int result;
	

	FD_ZERO(&rd1);
	FD_SET(hdle1, &rd1);  
	FD_SET(hdle2, &rd1);
     	result = select(max+1, &rd1, NULL, NULL, NULL); //waiting 

     	if (FD_ISSET(hdle1, &rd1) ) {
      		printf("waiting for the message\n");
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &cliaddr,
				&len);
       		 buffer[n] = '\0';
	
		printf("After recvfrom()\n");
	
		printf("buffer is %s\n",buffer);
		if(strcmp(buffer,fail)==0) 
    		{
         	//printf("end the programm.");
	  	 break;
    		} 
		
	
    		}

    	 if (FD_ISSET(hdle2, &rd1)) {
		
     	 	n = read(0, (char*)buffer, MAXLINE);
		buffer[n] = '\0';
		(char*)strcpy((char*)message, (char*)buffer);
		printf("After recvfrom()\n");
		printf("buffer is %s\n",buffer);


		sendto(sockfd, (const char *)buffer, strlen(buffer),
			MSG_CONFIRM,(const struct sockaddr *) &cliaddr,
			len);
		printf("message from keyborad sent.\n");

		if(strcmp(message,"exit\n")==0) 
    		{
         	//printf("end the programm.");
	  	 break;
    		} 
    		} 	
		

	}


	//printf("waiting for the message\n");
	//n = recvfrom(sockfd, (char *)buffer, MAXLINE,
				//MSG_WAITALL, MSG_PEEK, ( struct sockaddr *) &cliaddr,
				//&len);
        //buffer[n] = '\0';
	
	//printf("After recvfrom()\n");
	
	//printf("buffer is %s\n",buffer);
	
	
	//printf("len of hello buffer %ld \n",strlen(hello));
	
	//int value = strcmp (buffer, close);

	//if(strcmp(buffer,fail)==0) 
    	//{
         
	   //break;
    	//} 
	
	 	
	
	//sendto(sockfd, (const char *)&n, sizeof(n),
	//MSG_CONFIRM, MSG_PEEK, (const struct sockaddr *) &cliaddr,
			//len);
	//printf("Client : %s length rec %d \n", buffer,n);
		
	//printf("Hello message sent.\n");
	//}
 	

//server acting as client

	while(1){
	printf("Type your message:");
	scanf("%s",hello1);	

	sendto(sockfd1, (const char *)hello1, strlen(hello1),
		MSG_CONFIRM,(const struct sockaddr *) &servaddr1,
			sizeof(servaddr1));
	printf("Hello message sent.\n");
	if(strcmp(hello1,fail)==0) 
    	{
         
	    break;
    	} 
	n1 = recvfrom(sockfd1, (char *)buffer1, MAXLINE,
				MSG_WAITALL,(struct sockaddr *) &servaddr1,
				&len1);	
			
       	buffer1[n1] = '\0';
	printf("After recvfrom()\n");
	printf("buffer1 is %s\n",buffer1);
	
	
	}	
	

	return 0;
}

