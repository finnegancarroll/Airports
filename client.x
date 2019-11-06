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

struct location{
  char* city;
  char* state;
};

program CLIENT {
 version CLIENT_VERS {
 planeListRet getPlaceAirports(location) = 1;
 } = 1;
} = 0x36459328; 
