/*
This is a server program which demonstrates the support of IPv6 as well as IPv4 addressing to establish
a network connection.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include "errexit.h"

int errexit(const char *format, ...);
int TCPdaytimed(int fd);
int passivesock(int qlen);
#define QLEN 5

int passivesock(int qlen)
{
	struct sockaddr_in6 sin; /* an Internet endpoint address */
	struct servent* ser;
	ser = getservbyname("daytime", "tcp");
	if (ser == NULL)
		errexit("tcp daytime is an unknown service: %s\n", strerror(errno));
	int s; /* socket descriptor and socket type */
	memset(&sin, 0, sizeof(sin));
	sin.sin6_flowinfo = 0;
	sin.sin6_family = AF_INET6;
	sin.sin6_addr = in6addr_any;
	sin.sin6_port = ser->s_port;

	/* Allocate a socket */
	s = socket(AF_INET6, SOCK_STREAM, 0);	//PF to AF and 0 taken
	if (s < 0)
		errexit("can't create socket: %s\n", strerror(errno));
	/* Bind the socket */
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't bind to port: no. %s\n", strerror(errno));
	if (listen(s, qlen) < 0)
		errexit("can't listen on port: %s\n", strerror(errno));
	return s;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in6 fsin, clientadr; /* the from address of a client */
	int cliadrlen = sizeof(cliadrlen);
	memset(&fsin, 0, sizeof(fsin));
	char str[INET6_ADDRSTRLEN];
	bzero((char *) &fsin, sizeof(fsin));
	int msock, ssock; /* master & slave sockets */
	socklen_t alen = sizeof(fsin); /* from-address length */
	msock = passivesock(QLEN);
	while (1) {
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		getpeername(ssock, (struct sockaddr *)&clientadr, &cliadrlen);
		if(inet_ntop(AF_INET6, &clientadr.sin6_addr, str, sizeof(str))) {
			printf("Client address is %s\n", str);
			printf("Client port is: %d\n", ntohs(clientadr.sin6_port));
		}
		if (ssock < 0)
		errexit("accept failed: %s\n", strerror(errno));
		(void) TCPdaytimed(ssock);
		(void) close(ssock);
	}
}

int TCPdaytimed(int fd)
{
	char *pts; /* pointer to time string */
	time_t now; /* current time */
	char *ctime();
	(void) time(&now);
	pts = ctime(&now);
	(void) write(fd, pts, strlen(pts));
	return 0;
}
