#include "passNotes.h"

int chat(User *usr)
{
	char msgBuffer[MAX_MSG_SIZE] = {0};
	int bytesReceived = 0;
	int limit = MAX_MSG_SIZE + MAX_NICK_LENGTH + 2;
	User *ptr = usr;

	while(1)
	{
		bytesReceived = 0;
		memset(&msgBuffer, 0, sizeof msgBuffer);
		msgBuffer[0] = '\0';

		if((bytesReceived = recv(usr->sockNum, (void *) msgBuffer, limit, 
						MSG_WAITALL)) != -1)
		{
			printf("Received: \"%s\"\n", msgBuffer);

			while (ptr != NULL) // Go to head.
				ptr = ptr->prev;

			while (ptr != NULL) // Now traverse.
			{
				if(send(ptr->sockNum, msgBuffer, sizeof msgBuffer, 0) == -1)
					perror("send");
				ptr = ptr->next;
			}
		}
	}
	return 0;
}
