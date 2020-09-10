#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX 256

void client(int* client_send, int* client_receive) {

	close(client_send[0]); // READ pipe
	close(client_receive[1]); // WRITE pipe

	char data[MAX];

	while (true) {
		int start, end;
		printf("Start: ");
		scanf("%d", &start);
		printf("End: ");
		scanf("%d", &end);

		sprintf(data, "%d %d", start, end);
		write(client_send[1], data, strlen(data) + 1);

		read(client_receive[0], data, sizeof(data));
		printf("Client received: %s\n", data);
	}

}