#include "places.h"
#include <errno.h>

void freePlaneList(planeListRet list);

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
  errno = 0;//clear garbage data
	static planeListRet result_1;
  //Free memory from last call
    //MAKES SECOND RUN CRASH
    //xdr_free((xdrproc_t)xdr_planeListRet, (char*)&result_1); 
  
  //Sever code///////////
 
  //SERVER CODE HERE
	//SERVER CODE HERE
  
  result_1.planeListRet_u.airp.p = "H";
  result_1.planeListRet_u.airp.port1 = "E";
  result_1.planeListRet_u.airp.port2 = "XILAPHONE";
  result_1.planeListRet_u.airp.port3 = "X";
  result_1.planeListRet_u.airp.port4 = "L";
  result_1.planeListRet_u.airp.port5 = "O";
  
  //SERVER CODE HERE
	//SERVER CODE HERE
	
  //result.err = errno;
  return &result_1;
}