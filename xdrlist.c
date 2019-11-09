//Structures with overlaping plane.h and places.h definitions
#include "places.h"
#include "plane.h"

bool_t
xdr_acronym (XDR *xdrs, acronym *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXLEN))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportName (XDR *xdrs, airportName *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, objp, MAXLEN))
		 return FALSE;
	return TRUE;
}

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

	 if (!xdr_acronym (xdrs, &objp->acr))
		 return FALSE;
	 if (!xdr_airportName (xdrs, &objp->name))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->lon))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->lat))
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