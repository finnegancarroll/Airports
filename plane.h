/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PLANE_H_RPCGEN
#define _PLANE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXLEN 500

typedef char *portInfo;

typedef char *placeInfo;

typedef char *hostName;

typedef char *placeName;

typedef char *stateName;

#ifndef AIRPORTS
#define AIRPORTS
struct airports {
	placeInfo p;
	portInfo port1;
	portInfo port2;
	portInfo port3;
	portInfo port4;
	portInfo port5;
};
typedef struct airports airports;
#endif

#ifndef LISTRET
#define LISTRET
struct planeListRet {
	int err;
	union {
		airports airp;
	} planeListRet_u;
};
typedef struct planeListRet planeListRet;
#endif

struct location {
	hostName host;
	placeName place;
	stateName state;
};
typedef struct location location;

#define PLACE_LOOKUP_PROG 0x66454318
#define PLACE_LOOKUP_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define QUERY_PLACES 1
extern  planeListRet * query_places_1(location *, CLIENT *);
extern  planeListRet * query_places_1_svc(location *, struct svc_req *);
extern int place_lookup_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define QUERY_PLACES 1
extern  planeListRet * query_places_1();
extern  planeListRet * query_places_1_svc();
extern int place_lookup_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_portInfo (XDR *, portInfo*);
extern  bool_t xdr_placeInfo (XDR *, placeInfo*);
extern  bool_t xdr_hostName (XDR *, hostName*);
extern  bool_t xdr_placeName (XDR *, placeName*);
extern  bool_t xdr_stateName (XDR *, stateName*);
extern  bool_t xdr_airports (XDR *, airports*);
extern  bool_t xdr_planeListRet (XDR *, planeListRet*);
extern  bool_t xdr_location (XDR *, location*);

#else /* K&R C */
extern bool_t xdr_portInfo ();
extern bool_t xdr_placeInfo ();
extern bool_t xdr_hostName ();
extern bool_t xdr_placeName ();
extern bool_t xdr_stateName ();
extern bool_t xdr_airports ();
extern bool_t xdr_planeListRet ();
extern bool_t xdr_location ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PLANE_H_RPCGEN */