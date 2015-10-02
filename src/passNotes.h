#ifndef PASSNOTES_H
#define PASSNOTES_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h> 
#include <errno.h>

#define PORT "40000"
#define MAX_MSG_SIZE 1024
#define BACKLOG 5

/* Following is a hacky way to get color text. Including one of the following
strings at the start of a printf will make ALL text the corresponding color
until the "NONE" color is included in a printf. 
This gets used in the tests for colored PASS and FAIL messages. */
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define NONE "\x1B[0m"

// This function helps provide IP agnosticism re: IPv4 or IPv6.
void *get_in_addr(struct sockaddr *sa)
{
	if(sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*) sa)->sin_addr);

	return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

// Handles commands that start with '/'. The id = 0 for client and 1 for server
int handleCommands(const char *command, int sockfd, int id)
{
	// Client sends "/ping", server responds with "pong!", IRC style.
	if ((strcasecmp(command, (const char *) "/ping") == 0) && (id == 0))
	{
		if (send(sockfd, "/ping", 6, 0) == -1)
		{
			perror("send");
			return -1;
		}
	}

	if ((strcasecmp(command, (const char *) "/ping") == 0) && (id == 1))
	{
		if (send(sockfd, "pong!", 6, 0) == -1)
		{
			perror("send");
			return -1;
		}
	}
	return 0;
}

#endif // PASSNOTES_H
