#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define ReadEnd 0
#define WriteEnd 1

void client(int *client2server, int *server2client)
{

	close(client2server[ReadEnd]);
	close(server2client[WriteEnd]);

	char data[MAX];

	while (true)
	{
		int start, end;
		printf("Enter: (start end) (0 0 to quit): ");
		scanf("%d %d", &start, &end);
		sprintf(data, "%d %d", start, end);
		write(client2server[WriteEnd], data, strlen(data) + 1);

		if (start == 0 && end == 0) {
			close(client2server[WriteEnd]);
			exit(0);
		}

		read(server2client[ReadEnd], data, sizeof(data));
		printf("Client received: %s\n", data);
	}
}