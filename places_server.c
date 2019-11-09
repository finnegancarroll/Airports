#include "places.h"
#include <errno.h>

void freePlaneList(planeListRet list);

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap 
  errno = 0;//clear garbage data
	static planeListRet result_1;
  
  //Sever code///////////
 
  result_1.planeListRet_u.airp.p = "LOCATION INFO";
  result_1.planeListRet_u.airp.port1 = "AIRPORT1";
  result_1.planeListRet_u.airp.port2 = "AIRPORT2";
  result_1.planeListRet_u.airp.port3 = "AIRPORT3";
  result_1.planeListRet_u.airp.port4 = "AIRPORT4";
  result_1.planeListRet_u.airp.port5 = "AIRPORT5";
	
  result_1.err = errno;
  return &result_1;
}