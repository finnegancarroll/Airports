/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "places.h"

bool_t
xdr_airportList (XDR *xdrs, airportList *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)objp, sizeof (struct airports), (xdrproc_t) xdr_airports))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airports (XDR *xdrs, airports *objp)
{
	register int32_t *buf;

	 if (!xdr_pointer (xdrs, (char **)&objp->acr, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_pointer (xdrs, (char **)&objp->name, sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->lon))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->lat))
		 return FALSE;
	 if (!xdr_airportList (xdrs, &objp->next))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_planeListRet (XDR *xdrs, planeListRet *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_pointer (xdrs, (char **)&objp->planeListRet_u.airportList, sizeof (airports), (xdrproc_t) xdr_airports))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}

bool_t
xdr_position (XDR *xdrs, position *objp)
{
	register int32_t *buf;

	 if (!xdr_float (xdrs, &objp->lon))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->lat))
		 return FALSE;
	return TRUE;
}