typedef struct airports* airportList;

struct airports{
  char* acr;
  char* name;
  float lon;
  float lat;
  airportList next;
};

union planeListRet switch(int err){
	case 0:
    airports* airportList;
	default:
    void;	
};

struct position{
  float lon;
  float lat;
};

program AIRPORT_LOOKUP_PROG {
 version AIRPORT_LOOKUP_VERS {
 planeListRet QUERY_AIRPORTS(position) = 1;
 } = 1;
} = 0x26459329; 
