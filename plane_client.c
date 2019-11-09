#include "plane.h"
#include <iostream>

void
place_lookup_prog_1(char *host)
{
	CLIENT *clnt = nullptr;
	planeListRet *result_1 = nullptr;
	location  query_places_1_arg;
  //Init to nullptr so rpc has stopping point
  //These values cannot be nullptr!
  query_places_1_arg.place = "NoCitySpecified";
  query_places_1_arg.state = "NoStateSpecified";

  //PASSING THE SAME HOSTNAME FOR NOW, BOTH SERVERS NOT ALWAYS ON LOCALHOST
  query_places_1_arg.host = "localhost";

  #ifndef	DEBUG
	clnt = clnt_create (host, PLACE_LOOKUP_PROG, PLACE_LOOKUP_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
  #endif

	result_1 = query_places_1(&query_places_1_arg, clnt);
	if (result_1 == (planeListRet *) NULL) {
		clnt_perror (clnt, "call failed");
	}
  
  //PRINTING ERROR TO TEST, SHOULD BE 14
  printf("Err is: %d\n", result_1->err);
  
  #ifndef	DEBUG
	clnt_destroy (clnt);
  #endif
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
