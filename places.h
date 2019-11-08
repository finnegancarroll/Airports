#ifndef _PLACES_H_RPCGEN
#define _PLACES_H_RPCGEN

#include <rpc/rpc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef AIRPORTS
#define AIRPORTS
typedef struct airports *airportList;

struct airports {
	char *acr;
	char *name;
	float lon;
	float lat;
	airportList next;
};
typedef struct airports airports;
#endif

#ifndef LISTRET
#define LISTRET
struct planeListRet {
	int err;
	union {
		airports *airportList;
	} planeListRet_u;
};
typedef struct planeListRet planeListRet;
#endif

struct position {
	float lon;
	float lat;
};
typedef struct position position;

#define AIRPORT_LOOKUP_PROG 0x26459329
#define AIRPORT_LOOKUP_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define QUERY_AIRPORTS 1
extern  planeListRet * query_airports_1(position *, CLIENT *);
extern  planeListRet * query_airports_1_svc(position *, struct svc_req *);
extern int airport_lookup_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define QUERY_AIRPORTS 1
extern  planeListRet * query_airports_1();
extern  planeListRet * query_airports_1_svc();
extern int airport_lookup_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
#ifndef XDRFUNCS
#define XDRFUNCS
extern  bool_t xdr_airportList (XDR *, airportList*);
extern  bool_t xdr_airports (XDR *, airports*);
extern  bool_t xdr_planeListRet (XDR *, planeListRet*);
extern  bool_t xdr_position (XDR *, position*);
#endif

#else /* K&R C */
extern bool_t xdr_airportList ();
extern bool_t xdr_airports ();
extern bool_t xdr_planeListRet ();
extern bool_t xdr_position ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PLACES_H_RPCGEN */
