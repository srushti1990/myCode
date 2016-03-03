/*
This program is the header for the SocketOption.c file.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include "errexit.h"
union val {
int i_val;
long l_val;
struct linger linger_val;
struct timeval timeval_val;
} val;
static char strres[128];
static char *sock_str_flag(union val *, int);
static char *sock_str_int(union val *, int);
static char *sock_str_linger(union val *, int);
static char *sock_str_timeval(union val *, int);

typedef unsigned short u_short;
int errexit(const char *format, ...);
u_short portbase = 0; 
int passivesock(int qlen) 
{
	struct protoent *ppe; /* pointer to protocol information entry*/
	struct sockaddr_in sin; /* an Internet endpoint address */
	int fd, type; /* socket descriptor and socket type */
	socklen_t len;
	int rcvbuf1 = 10000, sndbuf1 = 10000, result, rcvbuf2, sndbuf2;
	int optionlen;
	struct sock_opts *ptr;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;

	/* Map protocol name to protocol number */
	sin.sin_port = htons(49000);
	
	fd = socket(PF_INET, SOCK_STREAM, 0);
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_BROADCAST, &val, &len) != -1)
		printf("SO_BROADCAST: default = %s\n", sock_str_flag (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_DEBUG, &val, &len) != -1)
		printf("SO_DEBUG: default = %s\n", sock_str_flag (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_DONTROUTE, &val, &len) != -1)
		printf("SO_DONTROUTE: default = %s\n", sock_str_flag (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_ERROR, &val, &len) != -1)
		printf("SO_ERROR: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &val, &len) != -1)
		printf("SO_KEEPALIVE: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_LINGER, &val, &len) != -1)
		printf("SO_LINGER: default = %s\n", sock_str_linger (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_OOBINLINE, &val, &len) != -1)
		printf("SO_OOBINLINE: default = %s\n", sock_str_flag (&val, len));
		len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &val, &len) != -1)
		printf("SO_RCVBUF: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &val, &len) != -1)
		printf("SO_SNDBUF: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_RCVLOWAT, &val, &len) != -1)
		printf("SO_RCVLOWAT: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_SNDLOWAT, &val, &len) != -1)
		printf("SO_SNDLOWAT: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &val, &len) != -1)
		printf("SO_RCVTIMEO: default = %s\n", sock_str_timeval (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &val, &len) != -1)
		printf("SO_SNDTIMEO: default = %s\n", sock_str_timeval (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, &len) != -1)
		printf("SO_REUSEADDR: default = %s\n", sock_str_flag (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, SOL_SOCKET, SO_TYPE, &val, &len) != -1)
		printf("SO_TYPE: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, IPPROTO_IP, IP_TOS, &val, &len) != -1)
		printf("IP_TOS: default = %s\n", sock_str_int (&val, len));
	len = sizeof(val);
	if(getsockopt(fd, IPPROTO_IP, IP_TTL, &val, &len) != -1)
		printf("SO_TYPE: default = %s\n", sock_str_int (&val, len));
	/* Setting the socket options */
	optionlen = sizeof sndbuf1;
	result = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &sndbuf1, &optionlen);
	if(result)
		printf("SO_SNDBUF setting failed\n");
	optionlen = sizeof rcvbuf1;
	result = setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf1, &optionlen);
	if(result)
		printf("SO_RCVBUF setting failed\n");
	/*Getting the set options */
	optionlen = sizeof sndbuf2;
	result = getsockopt(fd, SOL_SOCKET, SO_SNDBUF, &sndbuf2, &optionlen);
	if(result)
		printf("SO_SNDBUF getting failed\n");
	optionlen = sizeof rcvbuf2;
	result = getsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf2, &optionlen);
	if(result)
		printf("SO_RCVBUF getting failed\n");

	/*Printing the set options */
	printf("Send-buffer size set:%d \n", sndbuf2);
	printf("Receive-buffer size set:%d \n", rcvbuf2);

	if (bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't bind to port: no. %s\n", sin.sin_port, strerror(errno));
	if (listen(fd, qlen) < 0)
		errexit("can't listen on port: %s\n", sin.sin_port, strerror(errno));
	return fd;
}

static char * sock_str_int(union val *ptr, int len)
{
	if (len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%d", ptr->i_val);
	return(strres);
}

static char * sock_str_flag(union val *ptr, int len) {
	if (len != sizeof(int))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
	else
		snprintf(strres, sizeof(strres), "%s", (ptr->i_val == 0) ? "off" : "on");
	return(strres);
 }
static char * sock_str_linger(union val *ptr, int len)
{
	struct linger *lptr = &ptr->linger_val;
	if (len != sizeof(struct linger))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct linger)", len);
	else
		snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d", lptr->l_onoff, lptr->l_linger);
	return(strres);
}

static char * sock_str_timeval(union val *ptr, int len)
{
	struct timeval *tvptr = &ptr->timeval_val;
	if (len != sizeof(struct timeval))
		snprintf(strres, sizeof(strres), "size (%d) not sizeof(struct timeval)", len);
	else
		snprintf(strres, sizeof(strres), "%d sec, %d usec", tvptr->tv_sec, tvptr->tv_usec);
	return(strres);
}
