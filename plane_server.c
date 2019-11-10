#include "plane.h"
#include "places.h"
#include <errno.h>

//Copies heap allocated planeListRet into stack allocated version
void ptrToStatic(planeListRet &s, planeListRet *ptr);
//Takes cityname and state name and sets lat and lon of that location
//Also sets place info for city state
const char* setCoords(location *loc, double &lat, double &lon);

planeListRet* query_places_1_svc(location *argp, struct svc_req *rqstp)
{
  //No need to xdr_free(), no structures allocated on the heap 
  errno = 0;//clear garbage data
  static planeListRet result_1;	
  planeListRet *resultPtr = nullptr;
  CLIENT *clnt = nullptr;
  position query_airports_1_arg;//just two doubles
  //Use the city and state name to find client coordinates 
  const char* info = setCoords(argp, query_airports_1_arg.lat, query_airports_1_arg.lon);

  #ifndef	DEBUG	
  clnt = clnt_create (argp->host, AIRPORT_LOOKUP_PROG, AIRPORT_LOOKUP_VERS, "udp");
  #endif
  
  errno = 0;//clnt_create is setting errno to 13 = no permission
  resultPtr = query_airports_1(&query_airports_1_arg, clnt);
  ptrToStatic(result_1, resultPtr);  
  
  #ifndef	DEBUG
  //Free xdr memory
  clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)resultPtr); 
  clnt_destroy(clnt);
  #endif

  result_1.planeListRet_u.airp.p = (char*)info;
  result_1.err = errno;
	return &result_1;
}

void ptrToStatic(planeListRet &s, planeListRet *ptr){
  
  s.planeListRet_u.airp.p = ptr->planeListRet_u.airp.p;
  
  s.planeListRet_u.airp.port1 = ptr->planeListRet_u.airp.port1;
  ptr->planeListRet_u.airp.port1 = nullptr;  
  s.planeListRet_u.airp.port2 = ptr->planeListRet_u.airp.port2;
  ptr->planeListRet_u.airp.port2 = nullptr;  
  s.planeListRet_u.airp.port3 = ptr->planeListRet_u.airp.port3;
  ptr->planeListRet_u.airp.port3 = nullptr;  
  s.planeListRet_u.airp.port4 = ptr->planeListRet_u.airp.port4;
  ptr->planeListRet_u.airp.port4 = nullptr;  
  s.planeListRet_u.airp.port5 = ptr->planeListRet_u.airp.port5;
  ptr->planeListRet_u.airp.port5 = nullptr;  
} 

const char* setCoords(location *loc, double &lat, double &lon){
  ////////////USE THE LOCATION(CITY/STATE) TO FIND COORDINATES(LAT/LON)//////////// 
  ////////////SET INFO TO THE CITY INFORMATION LINE OF THE OUTPUT//////////// 
  ////////////SET ERRNO = 2//////////// FOR LOCATION NOT FOUND
    
  ////////////TEST////////////
 
  lat = 40.7128;
  lon = 74.0060;

  return "PUT PLACE INFO HERE!";
  ////////////TEST////////////
}