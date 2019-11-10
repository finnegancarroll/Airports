#include "places.h"
#include <errno.h>
#include <vector>

//Takes coordinates of client and outputs 5 closes airport info
void fiveClosest(position *p, planeListRet &list);

planeListRet *
query_airports_1_svc(position *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap 
  errno = 0;//clear garbage data
	static planeListRet result_1;

  fiveClosest(argp, result_1);
	
  result_1.err = errno;
  return &result_1;
}

void fiveClosest(position *p, planeListRet &list){
  ////////////IMPLEMENT THIS FUNCTION//////////// 
  ////////////USE THE COORDINATES(LAT/LON) TO FINE 5 NEAREST AIRPORTS//////////// 
  ////////////USE THE COORDINATES(LAT/LON) TO FINE 5 NEAREST AIRPORTS//////////// 
  ////////////USE THE COORDINATES(LAT/LON) TO FINE 5 NEAREST AIRPORTS//////////// 
  
  ////////////TEST////////////
  if(p->lat == 12.0 && p->lon == 15.0){
    list.planeListRet_u.airp.p = "You're in Seattle: Here's some test output";
    list.planeListRet_u.airp.port1 = "You're in Seattle: Here's some test output";
    list.planeListRet_u.airp.port2 = "You're in Seattle: Here's some test output";
    list.planeListRet_u.airp.port3 = "You're in Seattle: Here's some test output";
    list.planeListRet_u.airp.port4 = "You're in Seattle: Here's some test output";
    list.planeListRet_u.airp.port5 = "You're in Seattle: Here's some test output";
  }else{
    list.planeListRet_u.airp.p = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
    list.planeListRet_u.airp.port1 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
    list.planeListRet_u.airp.port2 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
    list.planeListRet_u.airp.port3 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
    list.planeListRet_u.airp.port4 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
    list.planeListRet_u.airp.port5 = "code: BRW, name: Barrow, state: AK, distance: 2698.693567";
  }
  ////////////TEST////////////
}





 
  