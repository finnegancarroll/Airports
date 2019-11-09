#include "plane.h"
#include "places.h"
#include <errno.h>

planeListRet *
query_places_1_svc(location *argp, struct svc_req *rqstp)
{
  static planeListRet result_1;	
  CLIENT *clnt = nullptr;
  position query_airports_1_arg;//just two doubles
  //Free memory from last call
    //xdr_free((xdrproc_t)xdr_planeListRet, (char*)&result_1); 
  //Init to nullptr so rpc has stopping point
  result_1.planeListRet_u.airp.p = "HELLO";
  result_1.planeListRet_u.airp.port1 = "HELLO";
  result_1.planeListRet_u.airp.port2 = "HELLO";
  result_1.planeListRet_u.airp.port3 = "HELLO";
  result_1.planeListRet_u.airp.port4 = "HELLO";
  result_1.planeListRet_u.airp.port5 = "HELLO";
  
  //Client code///////////
  
    /*
    #ifndef	DEBUG	
    clnt = clnt_create (argp->host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");
    #endif
    
    //result_1 = query_airports_1(&query_airports_1_arg, clnt);
    
    #ifndef	DEBUG
    //Free xdr memory
    clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)&result_1); 
    clnt_destroy(clnt);
    #endif
    */
  
  //Sever code///////////
  
  //SERVER CODE HERE
	//SERVER CODE HERE
  

  
  //SERVER CODE HERE
	//SERVER CODE HERE
  
  //Do not uncomment! code breaks!
  //result_1.err = errno;
	return &result_1;
}


