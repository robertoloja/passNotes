#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h> 
#include <errno.h>
#include <arpa/inet.h>
#include "passNotes.h"

#define SERVER_NAME "localhost"

int main(void)
{
	int sockfd;							// Will hold socket file descriptor.
	struct addrinfo hints, *servinfo;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;		// Friendly to IPv4 and IPv6.
	hints.ai_socktype = SOCK_STREAM;	// TCP connection.

	printf("\nAttempting to get connection info for %s:\t", SERVER_NAME);

	if ((rv = getaddrinfo(SERVER_NAME, PORT, &hints, &servinfo)) != 0)
	{
		printf(RED "FAILED%s", NONE);
		return 1;
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	// Here, the program should loop through all the results of the linked
	// list that starts at servinfo. But since this is a test using localhost
	// this is not necessary.
	printf("\nAttempting to open socket:\t\t\t\t");

	if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
					servinfo->ai_protocol)) == -1)
	{
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	printf("\nAttempting to connect to %s:\t\t\t", SERVER_NAME);

	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(sockfd);
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	// For the next test, the server should reply with "received test message".
}
