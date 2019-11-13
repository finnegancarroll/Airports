#include "plane.h"
#include <errno.h>
#include <iostream>

void printAirports(planeListRet *list);
void place_lookup_prog_1(char *phost, char *ahost, char *city, char *state);

int main (int argc, char *argv[])
{
	char *host1;//Places server
	char *host2;//Airports server
	char *city;//Client city
	char *state;//Client state
  
	if (argc < 5) {
		std::cout << "Usage: plane_client.c Server1Host Server2Host City State" << std::endl;
    exit (1);
	}
  
	host1 = argv[1];
	host2 = argv[2];
	city = argv[3];
	state = argv[4];
  
	place_lookup_prog_1 (host1, host2, city, state);
  exit (0);
}

void place_lookup_prog_1(char *phost, char *ahost, char *city, char *state)
{
	CLIENT *clnt = nullptr;
	planeListRet *result_1;
	location query_places_1_arg;
  //Airports server hostname
  query_places_1_arg.host = ahost;
  query_places_1_arg.place = city;
  query_places_1_arg.state = state;

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
  
  //Print server errors
	result_1->err;
  errno = result_1->err;
	if(result_1->err > 0){
    perror("Server Error: ");
  }else{
    //Print resulting airport list
    printAirports(result_1);
  }
  
  #ifndef	DEBUG
  //Free xdr memory
  clnt_freeres(clnt, (xdrproc_t)xdr_planeListRet, (char *)result_1); 
	clnt_destroy(clnt);
  #endif
}

//Print 5 closest airports
void printAirports(planeListRet *list){
  printf(list->planeListRet_u.airp.p);
  std::cout << std::endl;
  printf(list->planeListRet_u.airp.port1);
  std::cout << std::endl;
  printf(list->planeListRet_u.airp.port2);
  std::cout << std::endl;
  printf(list->planeListRet_u.airp.port3);
  std::cout << std::endl;
  printf(list->planeListRet_u.airp.port4);
  std::cout << std::endl;
  printf(list->planeListRet_u.airp.port5);
  std::cout << std::endl;
}