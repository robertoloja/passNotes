#include "../src/passNotes.h"

#define SERVER_NAME "localhost"
#define TEST_MSG_SIZE 16

int main(void)
{
	int sockfd;							// Will hold socket file descriptor.
	struct addrinfo hints, *servinfo;
	int rv;
	char s[INET6_ADDRSTRLEN];
	char testMsg[] = "/Test_Message";
	char msgBuffer[TEST_MSG_SIZE];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;		// Friendly to IPv4 and IPv6.
	hints.ai_socktype = SOCK_STREAM;	// TCP connection.

	printf("\nGetting connection info for %s:\t", SERVER_NAME);

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
	printf("\nOpening socket:\t\t\t\t");

	if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
					servinfo->ai_protocol)) == -1)
	{
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	printf("\nConnecting to %s:\t\t", SERVER_NAME);

	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(sockfd);
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	inet_ntop(servinfo->ai_family, get_in_addr((struct sockaddr *) 
				servinfo->ai_addr),	s, sizeof s);
	freeaddrinfo(servinfo);

	printf("\nSending test message to %s:\t", SERVER_NAME);

	if (send(sockfd, testMsg, sizeof(testMsg) / sizeof('a'), 0) !=
			sizeof testMsg)
	{
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	printf("\nReceiving test message from %s:\t", SERVER_NAME);

	if (recv(sockfd, msgBuffer, TEST_MSG_SIZE, 0) != TEST_MSG_SIZE)
	{
		printf(RED "FAILED%s", NONE);
	} else {
		printf(GREEN "PASSED%s", NONE);
	}

	printf("\n\n");

	// TODO: Use threads to simulate multiple users.
}
