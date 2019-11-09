const MAXLEN = 255;
typedef string acronym<MAXLEN>;
typedef string airportName<MAXLEN>;
typedef struct airports* airportList;

struct airports{
  acronym acr;
  airportName name;
  double lon;
  double lat;
  airportList next;
};

union planeListRet switch(int err){
	case 0:
    airports* airportList;
	default:
    void;	
};

struct position{
  double lon;
  double lat;
};

program AIRPORT_LOOKUP_PROG {
 version AIRPORT_LOOKUP_VERS {
 planeListRet QUERY_AIRPORTS(position) = 1;
 } = 1;
} = 0x26459329; 
