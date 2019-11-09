const MAXLEN = 500;

typedef string portInfo<MAXLEN>;
typedef string placeInfo<MAXLEN>;

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

struct position{
  double lon;
  double lat;
};

program AIRPORT_LOOKUP_PROG {
 version AIRPORT_LOOKUP_VERS {
 planeListRet QUERY_AIRPORTS(position) = 1;
 } = 1;
} = 0x26459329; 
