/*
This is a server program which demonstrates the getsockopt() and setsockopt() functions. The header file 
included has the code for that.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "passivesockTCP.h"
typedef unsigned long u_long;
int passivesock(int qlen);
int errexit(const char *format, ...);

int main(int argc, char *argv[])
{
	struct sockaddr_in fsin; /* the from address of a client */
	char buf[1]; /* "input" buffer; any size > 0 */
	int sock; /* server socket */
	int alen; /* from-address length */
	int msock;
	char message[128] = "Hello Client\n";

	msock = passivesock(0);
	while (1) {
		alen = sizeof(fsin);
		sock = accept(msock, (struct sockaddr *) &fsin, &alen);
		if (sock < 0)
			errexit("accept failed: %s\n", strerror(errno));
		(void) write(sock, message, strlen(message));
		(void) close(sock);
	}
}
