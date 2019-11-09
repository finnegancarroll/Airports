const MAXLEN = 500;

typedef string portInfo<MAXLEN>;
typedef string placeInfo<MAXLEN>;

typedef string hostName<MAXLEN>;
typedef string placeName<MAXLEN>;
typedef string stateName<MAXLEN>;

struct airports{
  placeInfo p;
  portInfo port1;
  portInfo port2;
  portInfo port3;
  portInfo port4;
  portInfo port5;
};

union planeListRet switch(int err){
	case 0:
    airports airp;
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
