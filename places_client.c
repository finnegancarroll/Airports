/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "places.h"
#include "plane.h"

planeListRet *
query_places_1_svc(location *argp, struct svc_req *rqstp)
{
	static planeListRet  result;

	/*
	 * insert server code here
	 */

	return &result;
}

void
airport_lookup_prog_1(char *host)
{
	CLIENT *clnt;
	planeListRet  *result_1;
	position  query_airports_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = query_airports_1(&query_airports_1_arg, clnt);
	if (result_1 == (planeListRet *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

  while(true){
    //Wait for function call
  }
  
  exit (0);
}
