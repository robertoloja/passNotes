//TODO: REFACTOR REFACTOR REFACTOR
//TODO: TESTS TESTS TESTS
#include "passNotes.h"
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>

#define ID 0 // Client is 1

void sigchld_handler(int s);
int chat(User usr);
void *connectToChat(void *clientInfo);

int main(void)
{
	int sockfd, new_fd; 
	struct addrinfo hints, *servinfo;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	pthread_t clients[MAX_CLIENTS];
	int nextThread = 0;
	User users[MAX_CLIENTS];

	//char msgBuffer[MAX_MSG_SIZE];
	//int bytesReceived;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}

	// For this to be useful online (read: not just on localhost), this
	// line should be changed to iterate over the linked list that 
	// starts at servinfo until a socket can be created.
	sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
			servinfo->ai_protocol);

	// Allow port reuse.
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		perror("setsockopt");
		exit(1);
	}

	if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
	{
		close(sockfd);
		perror("server: bind");
	}

	freeaddrinfo(servinfo);

	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchld_handler; // reap dead processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");

	while(1)
	{
		sin_size = sizeof client_addr;
		new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);

		if (new_fd == -1)
		{
			perror("accept");
			continue;
		}

		inet_ntop(client_addr.ss_family, get_in_addr((struct sockaddr *)
					&client_addr), s, sizeof s);
		printf("server: got connection from %s\n", s);

		users[nextThread].sockNum = new_fd;
		users[nextThread].threadNum = nextThread;

		pthread_create(&clients[nextThread], NULL, connectToChat,
			   	(void *) &users[nextThread]);
		nextThread++;

		close(new_fd);
	}
}

void sigchld_handler(int s)
{
	int saved_errno = errno;
	while(waitpid(-1, NULL, WNOHANG) > 0);

	errno = saved_errno;
}

void *connectToChat(void *clientInfo)
{
	User *usr = (User *) clientInfo;
	chat(*usr);
	return NULL;
}

int chat(User *usr)
{
	//TODO: A while(1) loop to handle the connection.
	//TODO: A call to handleCommands.
	//TODO: Populate the usr struct. I.e. get nickname and channel.
	return 0;
}
