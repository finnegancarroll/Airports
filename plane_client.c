#include "plane.h"

void
place_lookup_prog_1(char *host)
{
	CLIENT *clnt;
	planeListRet  *result_1;
	location  query_places_1_arg;
  //Init to nullptr so rpc has stopping point
  query_places_1_arg.hostName = nullptr;
  query_places_1_arg.place = nullptr;
  query_places_1_arg.state = nullptr;

#ifndef	DEBUG
	clnt = clnt_create (host, PLACE_LOOKUP_PROG, PLACE_LOOKUP_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = query_places_1(&query_places_1_arg, clnt);
	if (result_1 == (planeListRet *) NULL) {
		clnt_perror (clnt, "call failed");
	}
  
  //PRINTING ERROR TO TEST
  printf("Err is: %d\n", result_1->err);
  
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	place_lookup_prog_1 (host);
exit (0);
}
