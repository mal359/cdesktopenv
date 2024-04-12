#include <EUSCompat.h>

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rtable3.h"
#define access_none_3 0x0 /* owner only */
#define access_read_3 0x1
#define access_write_3 0x2
#define access_delete_3 0x4
#define access_exec_3 0x8 /* execution permission is a hack! */

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

void *
_DtCm_rtable_ping_3(void *argp, _DtCm_Connection *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_ping,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_lookup_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_lookup,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_lookup_next_larger_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_lookup_next_larger,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_lookup_next_smaller_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_lookup_next_smaller,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_lookup_range_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_lookup_range,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_abbreviated_lookup_range_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_abbreviated_lookup_range,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_insert_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_insert,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_delete_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_delete,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_delete_instance_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_delete_instance,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_change_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_change,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_change_instance_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_change_instance,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_lookup_next_reminder_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_lookup_next_reminder,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Status_3 *
_DtCm_rtable_check_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Status_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_check,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Status_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Status_3 *
_DtCm_rtable_flush_table_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Status_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_flush_table,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Status_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
_DtCm_rtable_size_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_size,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Registration_Status_3 *
_DtCm_register_callback_3(Registration_3 *argp, _DtCm_Connection *clnt)
{
	static Registration_Status_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, register_callback,
		(xdrproc_t) _DtCm_xdr_Registration_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Registration_Status_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Registration_Status_3 *
_DtCm_deregister_callback_3(Registration_3 *argp, _DtCm_Connection *clnt)
{
	static Registration_Status_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, deregister_callback,
		(xdrproc_t) _DtCm_xdr_Registration_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Registration_Status_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Access_Status_3 *
_DtCm_rtable_set_access_3(Access_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Access_Status_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_set_access,
		(xdrproc_t) _DtCm_xdr_Access_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Access_Status_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Access_Args_3 *
_DtCm_rtable_get_access_3(Access_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Access_Args_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_get_access,
		(xdrproc_t) _DtCm_xdr_Access_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Access_Args_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

Table_Res_3 *
_DtCm_rtable_abbreviated_lookup_key_range_3(Table_Args_3 *argp, _DtCm_Connection *clnt)
{
	static Table_Res_3 clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_abbreviated_lookup_key_range,
		(xdrproc_t) _DtCm_xdr_Table_Args_3, (caddr_t) argp,
		(xdrproc_t) _DtCm_xdr_Table_Res_3, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

long *
_DtCm_rtable_gmtoff_3(void *argp, _DtCm_Connection *clnt)
{
	static long clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, rtable_gmtoff,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_long, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
