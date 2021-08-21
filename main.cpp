#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void server(int*, int*);
void client(int*, int*);

int main() {

	// pipe id's
	int client2serverFD[2]; // client => server
	int server2clientFD[2]; // server => client

	// create two (unnamed) pipes for bidirectional communication
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
	}
	else if (pid == 0) { // child process
		server(client2serverFD, server2clientFD);
	}
	else { // parent process
		client(client2serverFD, server2clientFD);
		// client has done. wait for server to exit
		for (;;) {
			int status;
			printf("waiting for child process to terminate\n");
			pid_t child_pid = wait(&status);
			if (child_pid == pid) {
				printf("child process has terminated with status = %d\n", status);
				break;
			}
		}
	}
}
