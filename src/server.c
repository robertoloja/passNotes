#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUMBER 40000

void chat(int sock);

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n, pid;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error((const char *) "ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_NUMBER);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error((const char *)"ERROR on binding");

	 // This block listens and creates new sockets (per connection?)
	 // N.B. that accept() halts execution until it makes a connection.
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

	 while(1)
	 {
		 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

		 if (newsockfd < 0) 
			  error((const char *) "ERROR on accept");

		 pid = fork();

		 if (pid < 0){
			 error((const char *) "ERROR on fork");
		 }

		 if (pid == 0)
		 {
			 close(sockfd);
			 chat(newsockfd);
			 exit(0);
		 } else close(newsockfd);
	 }
	 /* The following couple of lines allow reading from the new socket.
	    There is a cooresponding write() call in the client.

     bzero(buffer,1024);
     n = read(newsockfd,buffer,1023);

     if (n < 0) 
		 error((const char *) "ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18); // 18 is msg size

     if (n < 0) error((const char *) "ERROR writing to socket");
	 */

     return 0; 
}

// This is the meat of the server. 
// It should keep track of user names and route messages correctly.
void chat(int sock)
{
	int n;
	char buffer[256];

	bzero(buffer, 256);
	n = read(sock, buffer, 255);
	printf("Read from socket\n");

	if (n < 0)
		error((const char *) "ERROR reading from socket");

	n = write(sock, "i got the message", 17);
	if (n < 0)
		error((const char *) "ERROR writing to socket");
}
