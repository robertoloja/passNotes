#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT_NUMBER 40000
#define MAX_MSG_LENGTH 1024

typedef struct
{
	int childToParent[2];
	int parentToChild[2];
} pipes;

void chat(int sock);

void error(char *msg)
{
    perror(msg);
    exit(1);
}

char lastMessage[MAX_MSG_LENGTH];

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int pid;
	 //pipes commPipes;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 
        perror((const char *) "ERROR opening socket");

     memset(&serv_addr, 0, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_NUMBER);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
              perror((const char *)"ERROR on binding");

     listen(sockfd,5);
     clilen = sizeof(cli_addr);

	 while(1)
	 {
		 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
				 (socklen_t *) &clilen);

		 if (newsockfd < 0) 
			  perror((const char *) "ERROR on accept");

		 /* Establish two way communication with children processes.
		 pipe(commPipes.childToParent);
		 pipe(commPipes.parentToChild); */
		 pid = fork();

		 if (pid < 0){
			 perror((const char *) "ERROR on fork");
		 }

		 if (pid == 0)
		 {
			 close(sockfd);
			 /*close(commPipes.parentToChild[1]);
			 close(commPipes.childToParent[0]);*/
			 chat(newsockfd);
			 exit(0);
		 } else {
			 close(newsockfd);
			 /*close(commPipes.parentToChild[0]);
			 close(commPipes.childToParent[1]);*/
		 }
	 }
     return 0; 
}

void chat(int sock)
{
	int n;

	memset(&lastMessage, 0, MAX_MSG_LENGTH);
	n = read(sock, lastMessage, MAX_MSG_LENGTH);
	printf("Read from socket: %s\n", lastMessage);

	if (n < 0)
		perror((const char *) "ERROR reading from socket");

	n = write(sock, lastMessage, sizeof(lastMessage));
	if (n < 0)
		perror((const char *) "ERROR writing to socket");
}
