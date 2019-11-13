#include "places.h"

bool_t
xdr_position (XDR *xdrs, position *objp)
{
	register int32_t *buf;

	 if (!xdr_double (xdrs, &objp->lon))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->lat))
		 return FALSE;
	return TRUE;
}