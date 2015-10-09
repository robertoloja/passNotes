#include "../src/passNotes.h"
#include <pthread.h>

#define SERVER_NAME "localhost"
#define TEST_MSG "Test_Message"
#define TEST_MSG_SIZE 13
#define ID 0 // Server is 1. Client is 0.

void *testChat(void *param)
{
	return param;
}

int main(void)
{
	int sockfd;	
	struct addrinfo hints, *servinfo;
	int rv;
	char s[INET6_ADDRSTRLEN];
	int bytesReceived;
	char msgBuffer[MAX_MSG_SIZE];

	pthread_t clients[MAX_CLIENTS];
	int nextThread = 0;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;		// Friendly to IPv4 and IPv6.
	hints.ai_socktype = SOCK_STREAM;	// TCP connection.

	printf("\nGetting connection info for %s:\t", SERVER_NAME);
	if ((rv = getaddrinfo(SERVER_NAME, PORT, &hints, &servinfo)) != 0)
		printf(RED "FAILED%s", NONE);
	else
		printf(GREEN "PASSED%s", NONE);

	// Here, the program should loop through all the results of the linked
	// list that starts at servinfo. But since this is a test using localhost
	// this is not necessary.
	printf("\nOpening socket:\t\t\t\t");
	if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, 
					servinfo->ai_protocol)) == -1)
		printf(RED "FAILED%s", NONE);
	else
		printf(GREEN "PASSED%s", NONE);


	printf("\nConnecting to %s:\t\t", SERVER_NAME);
	if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(sockfd);
		printf(RED "FAILED%s", NONE);
	} else
		printf(GREEN "PASSED%s", NONE);
	inet_ntop(servinfo->ai_family, get_in_addr((struct sockaddr *) 
				servinfo->ai_addr),	s, sizeof s);
	freeaddrinfo(servinfo);


	printf("\nSending test message to %s:\t", SERVER_NAME);
	if (send(sockfd, TEST_MSG, TEST_MSG_SIZE, 0) != TEST_MSG_SIZE)
		printf(RED "FAILED%s", NONE);
	else
		printf(GREEN "PASSED%s", NONE);


	printf("\nUsing the /ping command:\t\t");
	if (handleCommands((const char *) "/ping", sockfd, 0) == -1 ||
		(bytesReceived = recv(sockfd, msgBuffer, MAX_MSG_SIZE - 1, 0) == -1) ||
		(strcasecmp(msgBuffer, (const char *) "pong!") != 0 ))
		printf(RED "FAILED%s", NONE);
	else
		printf(GREEN "PASSED%s", NONE);


	printf("\nSpawning new thread to simulate user:\t");
	if((pthread_create(&clients[nextThread], NULL, testChat, 
					(void *) &sockfd)) != 0)
		printf(RED "FAILED%s", NONE);
	else {
		printf(GREEN "PASSED%s", NONE);
		nextThread++;
	}

	printf("\nSimulating multiple users (2):\t\t");
	//second user has to connect and get an sockfd.
	//then one user sends a message, second user has to receive it.
	//vice versa.

	printf("\n\n");
}
