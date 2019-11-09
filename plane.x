const MAXLEN = 255;
typedef string acronym<MAXLEN>;
typedef string airportName<MAXLEN>;
typedef string hostName<MAXLEN>;
typedef string placeName<MAXLEN>;
typedef string stateName<MAXLEN>;
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

struct location{
  hostName host;
  placeName place;
  stateName state;
};

program PLACE_LOOKUP_PROG {
 version PLACE_LOOKUP_VERS {
 planeListRet QUERY_PLACES(location) = 1;
 } = 1;
} = 0x66454318; 
