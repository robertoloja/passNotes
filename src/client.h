#include "passNotes.h"

#define ID 1
#define SERVER "localhost"

int changeNick(User *userInfo)
{
	char name[MAX_NICK_LENGTH];

	printf("\nEnter username: ");
	scanf("%s", name);
	strcpy(name, userInfo->name);

	return 0;
}

int chat(User *userInfo)
{
	char message[MAX_MSG_SIZE];
	char toSend[MAX_MSG_SIZE + MAX_NICK_LENGTH + 2];

	while(1)
	{
		memset(&message, 0, sizeof message);
		memset(&toSend, 0, sizeof toSend);

		printf("Me: ");
		scanf(" %s", message);

		if(message[0] == '/')
		{
			if(handleCommands(message, userInfo->sockNum, ID) == 1)
				return 0;

		} else {
			strcat(toSend, userInfo->name);
			strcat(toSend, ": ");
			strcat(toSend, message);

			if(send(userInfo->sockNum, toSend, sizeof toSend, 0) == -1)
				perror("send");
		}
	}
	return 0;
}
