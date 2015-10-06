#include "passNotes.h"

#define SERVER "localhost"

int chat(User *userInfo);
int changeNick(User *userInfo);

int main(void)
{
	int sockfd;
	//char msgBuffer[MAX_MSG_SIZE];
	struct addrinfo hints, *servinfo, *res;
	User user, *usrPtr = &user;
	int rv;
	char s[INET6_ADDRSTRLEN];

	// Clear and populate the addrinfo hints.
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	// In case addrinfo fails.
	if((rv = getaddrinfo(SERVER, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// Navigate the linked list that starts at servinfo, to find valid addrs.
	for(res = servinfo; res != NULL; res = res->ai_next)
	{
		// Check if successfully created a socket.
		if((sockfd = socket(res->ai_family, res->ai_socktype, 
						res->ai_protocol)) == -1)
		{
			perror("client: socket");
			continue;
		}

		// Check if successfully connected to socket.
		if(connect(sockfd, res->ai_addr, res->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("client: connect");
			continue;
		}

		break;
	}

	// In case no valid address is found.
	if(res == NULL)
	{
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}

	// NetworkTOPresentation: Convert from local bit order to network bit order.
	inet_ntop(res->ai_family, get_in_addr((struct sockaddr *) res->ai_addr),
			s, sizeof s);
	printf("client: connecting to %s", s);

	// Don't need servinfo anymore; res points to the valid address.
	freeaddrinfo(servinfo);
	changeNick(usrPtr);

}

int chat(User *userInfo)
{
	return 0;
}

int changeNick(User *userInfo)
{
	char name[MAX_NICK_LENGTH];

	printf("Enter username: ");
	scanf(" %s", name);
	strcpy(name, userInfo->name);

	return 0;
}
