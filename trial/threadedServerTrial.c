// IT WORKS! Multiple simultaneous users!
#include "../passNotes/src/passNotes.h"
#include <pthread.h>

void *doThings(void * newfd)
{
	int new_fd = *(int *)newfd;
	char msgBuffer[MAX_MSG_SIZE];
	int bytesReceived;

	while(1)
	{
		if((bytesReceived = recv(new_fd, msgBuffer, 1023, 0)) == 0)
		{
			return NULL;
		}
		msgBuffer[bytesReceived + 1] = '\0';

		printf("\nReceived: %s\n", msgBuffer);
	}

	return NULL;
}

int main(void)
{
	int sockfd, new_fd;
	struct addrinfo hints, *servinfo;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	int yes = 1;
	pthread_t threads[5];
	int nextThread = 0;
	void *pointToFd = &new_fd;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(NULL, PORT, &hints, &servinfo);
	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
			servinfo->ai_protocol);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
	bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
	freeaddrinfo(servinfo);

	// Try the listen call in a while loop.
	while(1)
	{
		listen(sockfd, 5);
		sin_size = sizeof client_addr;
		new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);
		inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)
				&client_addr), s, sizeof s);
		printf("Got Connection from %s\n", s);

		pthread_create(&threads[nextThread], NULL, doThings, pointToFd);
	}
}
