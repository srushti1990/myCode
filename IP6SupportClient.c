/*
This is a client program which demonstrates the support of IPv6 alongwith IPv4 addressing to establish 
a network connection.
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "errexit.h"
extern int errno;
int TCPdaytime(const char *host, char *type);
int errexit(const char *format, ...);
#define LINELEN 128

int connectsock(const char *host, char *type)
{
	struct hostent *phe; /* pointer to host information entry */
	struct servent *pse; /* pointer to service information entry */
	struct protoent *ppe; /* pointer to protocol information entry*/
	struct sockaddr_in sin;
	struct addrinfo addr, *adrp;
	int i, s;
	if(*type == '6') {
		printf("Inside IPv6 socket connection\n");
		addr.ai_flags = 0;
		addr.ai_family = PF_INET6;
		addr.ai_socktype = SOCK_STREAM;
		addr.ai_protocol = 0;
		if((i = getaddrinfo( host, "daytime", &addr, &adrp)) != 0)
			errexit("getaddrinfo failed code: %d\n", i);
	
		/* Allocate a socket */
		s = socket(adrp->ai_family, adrp->ai_socktype, adrp->ai_protocol);
		if (s < 0)
			errexit("can't create socket: %s\n", strerror(errno));
		/* Connect the socket */
		if(connect(s, adrp->ai_addr, adrp->ai_addrlen) < 0)
			errexit("can't connect to %s: %s\n", host, strerror(errno));
		return s;
	}
	else {
		printf("Inside IPv4 socket connection\n");
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		if ( pse = getservbyname("daytime", "tcp") )
			sin.sin_port = pse->s_port;
		else
			errexit("can't get \"%s\" service entry\n", "daytime");

		if ( phe = gethostbyname(host) )
			memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
		else if ( (sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE )
			errexit("can't get \"%s\" host entry\n", host);

		s = socket(PF_INET, SOCK_STREAM, 0);
		if (s < 0)
			errexit("can't create socket: %s\n", strerror(errno));
		/* Connect the socket */
		if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
			errexit("can't connect to %s.%s: %s\n", host, "daytime", strerror(errno));
		return s;
	}
}

int main(int argc, char *argv[])
{
	char *host, *type = argv[1];
	printf("Type received is: %c\n", *type);
	if(*type == '6') {
		host = "::1";
		printf("Sending IPv6 request \n");
	}
	else if(*type == '4') {
		host = "localhost";
		printf("Sending IPv4 request \n");
	}
	else {
		errexit("Unexpected input for the IP version: %c \n", *type);
	}

	TCPdaytime(host, type);
	exit(0);
}

TCPdaytime(const char *host, char *type)
{
	char buf[LINELEN+1]; /* buffer for one line of text */
	int s, n; /* socket, read count */
	s = connectsock(host, type);
	while( (n = read(s, buf, LINELEN)) > 0) {
		buf[n] = '\0'; /* ensure null-terminated */
		(void) fputs( buf, stdout );
	}
}
