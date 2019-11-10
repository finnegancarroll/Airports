#include "places.h"
#include <errno.h>
#include <vector>

void freePlaneList(planeListRet list);

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap 
  errno = 0;//clear garbage data
	static planeListRet result_1;
  
  //Sever code///////////
 
  result_1.planeListRet_u.airp.p = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  result_1.planeListRet_u.airp.port1 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  result_1.planeListRet_u.airp.port2 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  result_1.planeListRet_u.airp.port3 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  result_1.planeListRet_u.airp.port4 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  result_1.planeListRet_u.airp.port5 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
	
  result_1.err = errno;
  return &result_1;
}