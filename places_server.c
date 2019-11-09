#include "places.h"
#include <errno.h>

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
	static planeListRet result;
  //Free memory from last call
  xdr_free((xdrproc_t)xdr_planeListRet, (char*)&result); 
  //Init to nullptr so rpc has stopping point
  result.planeListRet_u.airp.p = nullptr;
  result.planeListRet_u.airp.port1 = nullptr;
  result.planeListRet_u.airp.port2 = nullptr;
  result.planeListRet_u.airp.port3 = nullptr;
  result.planeListRet_u.airp.port4 = nullptr;
  result.planeListRet_u.airp.port5 = nullptr;

  //Sever code///////////
 
  //SERVER CODE HERE
	//SERVER CODE HERE
  
  
  
  //SERVER CODE HERE
	//SERVER CODE HERE
	
  //result.err = errno;
  return &result;
}