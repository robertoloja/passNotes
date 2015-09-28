// A simple server in the internet domain using TCP
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUMBER 40000

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, clilen;
     char buffer[1024];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        error((const char *) "ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_NUMBER);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              error((const char *)"ERROR on binding");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0) 
          error((const char *) "ERROR on accept");

     bzero(buffer,1024);
     n = read(newsockfd,buffer,1023);

     if (n < 0) 
		 error((const char *) "ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18); // 18 is msg size

     if (n < 0) error((const char *) "ERROR writing to socket");

     return 0; 
}
