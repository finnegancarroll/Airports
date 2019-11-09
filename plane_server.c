#include "plane.h"
#include "places.h"

planeListRet *
query_places_1_svc(location *argp, struct svc_req *rqstp)
{
  static planeListRet* result_1 = new planeListRet;	
	CLIENT *clnt = nullptr;
	position query_airports_1_arg;//just two doubles
  //Init to nullptr so rpc has stopping point
  result_1->planeListRet_u.airportList = nullptr;
  result_1->err = 0;
  
  //Client code///////////
  
  #ifndef	DEBUG
	
  clnt = clnt_create (argp->host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");    
  
  if (clnt == NULL) {
		clnt_pcreateerror ((*argp).host);
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
  
  //Sever code///////////
  
  //SERVER CODE HERE
	//SERVER CODE HERE
  
  //Add two to the result err to show the message made it through the plane_server
  result_1->err += 2;
  
  //SERVER CODE HERE
	//SERVER CODE HERE
  
	return result_1;
}


