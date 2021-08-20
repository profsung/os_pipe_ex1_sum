#include "common_includes.h"

void server(int* client2server, int* server2client) {

	close(client2server[WriteEnd]);
	close(server2client[ReadEnd]);

	char data[MAX];

	while (true) {
		read(client2server[ReadEnd], data, sizeof(data));
		int start, end;
		sscanf(data, "%d %d", &start, &end);
		if (start == 0 && end == 0) {
			close(server2client[WriteEnd]);
			exit(0);
		}
		printf("SERVER received: start = %d end = %d\n", start, end);

		// server computes sum
		int sum = 0;
		for (int i = start; i <= end; i++) {
			sum += i;
		}

		// server sends to client the computing results
		sprintf(data, "sum is %d", sum);
		write(server2client[WriteEnd], data, strlen(data) + 1);
	}

}