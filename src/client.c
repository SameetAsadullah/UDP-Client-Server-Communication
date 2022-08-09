// udp client driver program 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include<netinet/in.h> 
#include<unistd.h> 
#include<stdlib.h> 

#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100]; 
	char message[100]; 
	int sockfd, n, len; 
	struct sockaddr_in servaddr, recvaddr; 
	
	// clear servaddr 
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 
	
	// create datagram socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	// connect to server 
	if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
	{ 
		printf("\n Error : Connect Failed \n"); 
		exit(0); 
	} 

	// request to send datagram 
	// no need to specify server address in sendto 
	// connect stores the peers IP and port 
    len = sizeof(recvaddr);

	while (strcmp(buffer, "exit") != 0 && strcmp(message, "exit") != 0) {
        printf("Enter Message to Send: ");
        scanf("%s", &message);
        sendto(sockfd, message, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); 
	
	    // waiting for response
	    if (strcmp(message, "exit") != 0) {
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&recvaddr, &len);
	        printf("Message Received: ");
            puts(buffer);
        }
    } 

	printf("Server IP Address: %s\n", inet_ntoa(recvaddr.sin_addr));
    printf("Server Port: %d\n", (int)ntohs(recvaddr.sin_port));
	// close the descriptor 
	close(sockfd); 
} 