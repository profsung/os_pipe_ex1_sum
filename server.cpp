#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define ReadEnd  0
#define WriteEnd 1

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
		int sum = 0;
		for (int i = start; i <= end; i++) {
			sum += i;
		}

		sprintf(data, "sum is %d", sum);
		write(server2client[WriteEnd], data, strlen(data) + 1);
	}

}