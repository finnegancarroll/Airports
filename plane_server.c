#include "plane.h"
#include "places.h"
#include <errno.h>

void ptrToStatic(planeListRet &s, planeListRet *ptr);

planeListRet *
query_places_1_svc(location *argp, struct svc_req *rqstp)
{
  static planeListRet result_1;	
    //MAKES SECOND RUN CRASH
    //xdr_free((xdrproc_t)xdr_planeListRet, (char*)&result_1); 
  planeListRet *resultPtr = new planeListRet;
  CLIENT *clnt = nullptr;
  position query_airports_1_arg;//just two doubles
  //Free memory from last call  
  
  //Client code///////////  
  
  /*
  #ifndef	DEBUG	
  clnt = clnt_create (argp->host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");
  #endif
  
  resultPtr = query_airports_1(&query_airports_1_arg, clnt);
  
  #ifndef	DEBUG
  //Free xdr memory
  clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)&result_1); 
  clnt_destroy(clnt);
  #endif
  */
  
  //Sever code///////////
  
  //SERVER CODE HERE
	//SERVER CODE HERE
  
  ////PROOF THAT THE ptrToStatic FUNCTION WORKS ///////////
  result_1.planeListRet_u.airp.p = "H";
  result_1.planeListRet_u.airp.port1 = "E";
  result_1.planeListRet_u.airp.port2 = "L";
  result_1.planeListRet_u.airp.port3 = "L";
  result_1.planeListRet_u.airp.port4 = "L";
  result_1.planeListRet_u.airp.port5 = "O";
  
  resultPtr->planeListRet_u.airp.p = "H";
  resultPtr->planeListRet_u.airp.port1 = "E";
  resultPtr->planeListRet_u.airp.port2 = "L";
  resultPtr->planeListRet_u.airp.port3 = "P";
  resultPtr->planeListRet_u.airp.port4 = "M";
  resultPtr->planeListRet_u.airp.port5 = "E";
  /////////////////////////////////////////////////////////

  ptrToStatic(result_1, resultPtr);
    
  //SERVER CODE HERE
	//SERVER CODE HERE
  
	return &result_1;
}

void ptrToStatic(planeListRet &s, planeListRet *ptr){
  s.planeListRet_u.airp.p = ptr->planeListRet_u.airp.p;
  s.planeListRet_u.airp.port1 = ptr->planeListRet_u.airp.port1; 
  s.planeListRet_u.airp.port2 = ptr->planeListRet_u.airp.port2;
  s.planeListRet_u.airp.port3 = ptr->planeListRet_u.airp.port3;
  s.planeListRet_u.airp.port4 = ptr->planeListRet_u.airp.port4;
  s.planeListRet_u.airp.port5 = ptr->planeListRet_u.airp.port5;
} 