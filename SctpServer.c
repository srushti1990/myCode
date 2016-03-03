/*
Server program to implement SCTP transport layer protocol demonstrated to send time information to the 
client.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include "common.h"

int main()
{
  int listenSock, s, retval;
  struct sockaddr_in servaddr;
  struct sctp_initmsg initmsg;
  char buffer[MAX_BUFFER+1];
  time_t currentTime;

  listenSock = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );

  /* Accept connections from any interface */
  bzero( (void *)&servaddr, sizeof(servaddr) );
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
  servaddr.sin_port = htons(MY_PORT_NUM);

  retval = bind( listenSock, (struct sockaddr *)&servaddr, sizeof(servaddr) );

  /* Specify that a maximum of 5 streams will be available per socket */
  memset( &initmsg, 0, sizeof(initmsg) );
  initmsg.sinit_num_ostreams = 2;
  initmsg.sinit_max_instreams = 2;
  initmsg.sinit_max_attempts = 3;
  retval = setsockopt( listenSock, IPPROTO_SCTP, SCTP_INITMSG, 
                     &initmsg, sizeof(initmsg) );

  /* Place the server socket into the listening state */
  listen(listenSock, 2);

  /* Server loop... */
  while(1) {

    /* Await a new client connection */
    printf("Waiting for a connection\n");
    s = accept( listenSock, (struct sockaddr *)NULL, (int *)NULL );

    currentTime = time(NULL);

    /* Send local time on stream 0 (local time stream) */
    snprintf( buffer, MAX_BUFFER, "%s", ctime(&currentTime) );
    retval = sctp_sendmsg( s, (void *)buffer, (size_t)strlen(buffer), NULL, 0, 0, 0, LOCALTIME_STREAM, 0, 0 );

    /* Send GMT on stream 1 (GMT stream) */
    snprintf( buffer, MAX_BUFFER, "%s", asctime( gmtime( &currentTime ) ) );
    retval = sctp_sendmsg( s, (void *)buffer, (size_t)strlen(buffer), NULL, 0, 0, 0, GMT_STREAM, 0, 0 );

    close(s);
  }
  return 0;
}

