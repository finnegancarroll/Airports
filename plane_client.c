#include "plane.h"
#include <errno.h>
#include <iostream>

void
place_lookup_prog_1(char *phost, char *ahost)
{
	CLIENT *clnt = nullptr;
	planeListRet *result_1;
	location query_places_1_arg;
  //Airports server hostname
  query_places_1_arg.host = ahost;
  //These values cannot be nullptr!
  query_places_1_arg.place = "NoCitySpecified";
  query_places_1_arg.state = "NoStateSpecified";

  #ifndef	DEBUG
	clnt = clnt_create (phost, PLACE_LOOKUP_PROG, PLACE_LOOKUP_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (phost);
		exit (1);
	}
  #endif

	result_1 = query_places_1(&query_places_1_arg, clnt);
	if (result_1 == (planeListRet *) NULL) {
		clnt_perror (clnt, "call failed");
	}
    
  //////PRINT OUT SERVER RESULTS HERE!//////
  
  printf(result_1->planeListRet_u.airp.p);
  printf(result_1->planeListRet_u.airp.port1);
  printf(result_1->planeListRet_u.airp.port2);
  printf(result_1->planeListRet_u.airp.port3);
  printf(result_1->planeListRet_u.airp.port4);
  printf(result_1->planeListRet_u.airp.port5);
  std::cout << std::endl;
  
  //////PRINT OUT SERVER RESULTS HERE!//////
  
  //Print server errors
	errno = result_1->err;
	if(errno > 0){
    perror("Server Error:");
  }
  
  #ifndef	DEBUG
  //Free xdr memory
    //MAKES SECOND RUN CRASH!
    //clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)result_1); 
	clnt_destroy(clnt);
  #endif
}

int
main (int argc, char *argv[])
{
	char *host1;//Places server
	char *host2;//Airports server
  
	if (argc < 3) {
		std::cout << "Usage: plane_client.c hostname1 hostname2" << std::endl;
    exit (1);
	}
  
	host1 = argv[1];
	host2 = argv[2];
  
	place_lookup_prog_1 (host1, host2);
  exit (0);
}
