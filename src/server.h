#include "passNotes.h"

int chat(User *usr)
{
	char msgBuffer[MAX_MSG_SIZE] = {0};
	int bytesReceived = 0;
	int limit = MAX_MSG_SIZE + MAX_NICK_LENGTH + 2;
	int i;

	while(1)
	{
		msgBuffer[0] = '\0';
		memset(&msgBuffer, 0, sizeof msgBuffer);

		if((bytesReceived = recv(usr->sockNum, (void *) msgBuffer, limit,
					   	MSG_DONTWAIT)) != 0)
		{
			printf("Received: \"%s\"", msgBuffer);

			// Nope. usr is a pointer to an item in the array; that's why this
			// array has to be a linked list.
			for(i = 0; i < MAX_CLIENTS; i++)
			{
				if(usr[i].threadNum != 0)
				{
					if(send(usr[i].sockNum, msgBuffer, sizeof msgBuffer,
							   	0) == -1)
						perror("send");
				}
			}
		}
	}
	return 0;
}
