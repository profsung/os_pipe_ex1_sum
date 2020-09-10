#include <iostream>
using namespace std;

#include <unistd.h>
#include <string.h>
#define MAX 256

void server(int *, int *);
void client(int *, int *);

int main() {
	int client_send[2];
	int client_receive[2];
	// create a pipe
	if (pipe(client_send) < 0) {
		cerr << "cannot create a pipe." << endl;
		exit(1);
	}
	if (pipe(client_receive) < 0) {
		cerr << "cannot create a pipe." << endl;
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		cerr << "cannot fork()" << endl;
		exit(1);
	} else if (pid == 0) { // child process
		server(client_send, client_receive);
	} else { // parent process
		client(client_send, client_receive);
	}
}
