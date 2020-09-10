#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 256

void server(int* client_send, int* client_receive) {

	close(client_send[1]); // READ pipe
	close(client_receive[0]); // WRITE pipe

	char data[MAX];

	while (true) {
		read(client_send[0], data, sizeof(data));
		int start, end;
		sscanf(data, "%d %d", &start, &end);
		printf("SERVER: start = %d end = %d\n", start, end);
		int sum = 0;
		for (int i = start; i <= end; i++) {
			sum += i;
		}

		sprintf(data, "sum is %d", sum);
		write(client_receive[1], data, strlen(data) + 1);
	}

}