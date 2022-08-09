// server program for udp connection 
#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#define PORT 5000 
#define MAXLINE 1000 

// Driver code 
int main() 
{ 
	char buffer[100]; 
	char message[100]; 
	int listenfd, len; 
	struct sockaddr_in servaddr, cliaddr; 
	bzero(&servaddr, sizeof(servaddr)); 

	// Create a UDP Socket 
	listenfd = socket(AF_INET, SOCK_DGRAM, 0);		 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_family = AF_INET; 

	// bind server address to socket descriptor 
	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)); 
	
	//receive the datagram 
	len = sizeof(cliaddr); 
	
    while (strcmp(buffer, "exit") != 0 && strcmp(message, "exit") != 0) {
        int n = recvfrom(listenfd, buffer, sizeof(buffer), 
    			0, (struct sockaddr*)&cliaddr,&len); //receive message from server 
    	buffer[n] = '\0'; 
    	printf("Message Received: ");
        puts(buffer); 
		
	    // send the response
        if (strcmp(buffer, "exit") != 0) {
            printf("Enter Message to Send: ");
			scanf("%s", &message);
	        sendto(listenfd, message, MAXLINE, 0, 
	         	(struct sockaddr*)&cliaddr, sizeof(cliaddr));
        }
    }

    printf("Client IP Address: %s\n", inet_ntoa(cliaddr.sin_addr));
    printf("Client Port: %d\n", (int)ntohs(cliaddr.sin_port));
}