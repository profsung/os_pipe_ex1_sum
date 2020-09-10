#include <iostream>
using namespace std;

#include <unistd.h>
#include <string.h>
#define MAX 256

void server(int *, int *);
void client(int *, int *);

int main() {
	int client2serverFD[2];
	int server2clientFD[2];
	// create a pipe
	if (pipe(client2serverFD) < 0) {
		cerr << "cannot create a pipe." << endl;
		exit(1);
	}
	if (pipe(server2clientFD) < 0) {
		cerr << "cannot create a pipe." << endl;
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		cerr << "cannot fork()" << endl;
		exit(1);
	} else if (pid == 0) { // child process
		server(client2serverFD, server2clientFD);
	} else { // parent process
		client(client2serverFD, server2clientFD);
	}
}
