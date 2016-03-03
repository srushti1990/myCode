/*
Client program to implement SCTP transport layer protocol demonstrated to request time from the server.
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "common.h"

int main()
{
	int s, in, i, retval, flags;
  	struct sockaddr_in servaddr;
	struct sctp_sndrcvinfo sndrcvinfo;
	struct sctp_event_subscribe events;
	struct sctp_initmsg initmsg;
  	char buffer[MAX_BUFFER+1];

	s = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );

  	memset( &initmsg, 0, sizeof(initmsg) );
  	initmsg.sinit_num_ostreams = 2;
  	initmsg.sinit_max_instreams = 2;
  	initmsg.sinit_max_attempts = 3;
  	retval = setsockopt( s, IPPROTO_SCTP, SCTP_INITMSG, &initmsg, sizeof(initmsg) );

	bzero( (void *)&servaddr, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
  	servaddr.sin_port = htons(MY_PORT_NUM);
  	servaddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );

	retval = connect( s, (struct sockaddr *)&servaddr, sizeof(servaddr) );
	
	/* Enable receipt of SCTP Snd/Rcv Data via sctp_recvmsg */
  	memset( (void *)&events, 0, sizeof(events) );
  	events.sctp_data_io_event = 1;
  	retval = setsockopt( s, SOL_SCTP, SCTP_EVENTS, (const void *)&events, sizeof(events) );

	/* Message from the peer */
  	for (i = 0 ; i < 2 ; i++) 
	{
    		in = sctp_recvmsg( s, (void *)buffer, sizeof(buffer), (struct sockaddr *)NULL, 0, &sndrcvinfo, &flags );
    		if (in > 0) {
      			buffer[in] = 0;
	      		if (sndrcvinfo.sinfo_stream == LOCALTIME_STREAM) 
        			printf("Local time is %s", buffer);
			else if (sndrcvinfo.sinfo_stream == GMT_STREAM) 
		        	printf("GMT time is %s", buffer);
    		}
  	}

  	/* Close our socket and exit */
  	close(s);

  	return 0;
}
