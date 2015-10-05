#include "passNotes.h"

#define SERVER "localhost"

int main(void)
{
	int sockfd, numbytes;
	char msgBuffer[MAX_MSG_SIZE];
	struct addrinfo hints, *servinfo, *res;
	int rv;
	char s[INET6_ADDRSTRLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if((rv = getaddrinfo(SERVER, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	for(res = servinfo; res != NULL; res = res->ai_next)
	{
		if((sockfd = socket(res->ai_family, res->ai_socktype, 
						res->ai_protocol)) == -1)
		{
			perror("client: socket");
			continue;
		}

		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	if(res == NULL)
	{
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	inet_ntop(res->ai_family, get_in_addr((struct sockaddr *) res->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s", s);

	freeaddrinfo(servinfo);

	// All done with preliminary stuff. Actual client code goes in here.
}
