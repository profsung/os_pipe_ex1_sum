#include "common_includes.h"

void client(int *client2server, int *server2client)
{

	close(client2server[ReadEnd]);
	close(server2client[WriteEnd]);

	char data[MAX];

	while (true)
	{
		int start, end;
		int no;
		do
		{
			printf("Enter: (start end) (0 0 to quit): ");
			no = scanf("%d %d", &start, &end);

			// read the remaining chars typed
			char c;
			while ((c = getchar()) != '\n' && c != EOF) ;
		} while (no != 2);

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