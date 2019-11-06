union planeListRet switch(int err){
	case 0:
		airports* head;
	default:
void;	
};

struct airports{
  char* acr;
  char* name;
  float lon;
  float lat;
  airports* next;
};

struct position{
  float lon;
  float lat;
};

program PLACES {
 version PLACES_VERS {
 planeListRet getAirports(position) = 1;
 } = 1;
} = 0x26459329; 
