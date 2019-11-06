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

struct location{
  char* place;
  char* state;
};

program PLACE_LOOKUP_PROG {
 version PLACE_LOOKUP_VERS {
 planeListRet GETAIRPORTS(location) = 1;
 } = 1;
} = 0x66454318; 
