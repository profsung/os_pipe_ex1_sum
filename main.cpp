#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void server(int *, int *);
void client(int *, int *);

int main() {

	// pipe id's
	int client2serverFD[2];
	int server2clientFD[2];

	// create a pipe
	if (pipe(client2serverFD) < 0) {
		printf("cannot create a pipe.\n");
		exit(1);
	}
	if (pipe(server2clientFD) < 0) {
		printf("cannot create a pipe.\n");
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		printf("cannot fork()\n");
		exit(1);
	} else if (pid == 0) { // child process
		server(client2serverFD, server2clientFD);
	} else { // parent process
		client(client2serverFD, server2clientFD);
	}
}
