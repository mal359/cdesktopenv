#include <EUSCompat.h>

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "agent.h"
#include "rtable4.h"

bool_t
_DtCm_xdr_Update_Status (XDR *xdrs, Update_Status *objp)
{
	register int32_t *buf;

	 if (!xdr_enum (xdrs, (enum_t *) objp))
		 return FALSE;
	return TRUE;
}
