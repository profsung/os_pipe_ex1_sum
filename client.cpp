#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "my_defs.h"

void client(int *client2server, int *server2client)
{

	close(client2server[ReadEnd]);
	close(server2client[WriteEnd]);

	char data[MAX];
	char line[MAX];

	while (true)
	{
		int start, end;
		int no;
		for (;;)
		{
			printf("Enter: (start end) (0 0 to quit): ");
			fgets(line, MAX, stdin);
			no = sscanf(line, "%d %d", &start, &end);
			if (no == 2)
				break;
			printf("\tEnter two integers (start end)\n");
		}

		// client sends start/end to server to request for computing(sum)
		sprintf(data, "%d %d", start, end);
		write(client2server[WriteEnd], data, strlen(data) + 1);

		if (start == 0 && end == 0)
		{
			close(client2server[WriteEnd]);
			exit(0);
		}

		// client receives computation results from server
		read(server2client[ReadEnd], data, sizeof(data));
		printf("Client received: %s\n", data);
	}
}