#include <EUSCompat.h>

/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "cm.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

void *
cms_ping_5(void *argp, _DtCm_Connection *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_PING,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

cms_list_calendars_res *
cms_list_calendars_5(void *argp, _DtCm_Connection *clnt)
{
	static cms_list_calendars_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_LIST_CALENDARS,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_cms_list_calendars_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_open_res *
cms_open_calendar_5(cms_open_args *argp, _DtCm_Connection *clnt)
{
	static cms_open_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_OPEN_CALENDAR,
		(xdrproc_t) xdr_cms_open_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_open_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_create_calendar_5(cms_create_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_CREATE_CALENDAR,
		(xdrproc_t) xdr_cms_create_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_remove_calendar_5(cms_remove_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_REMOVE_CALENDAR,
		(xdrproc_t) xdr_cms_remove_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_register_5(cms_register_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_REGISTER,
		(xdrproc_t) xdr_cms_register_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_unregister_5(cms_register_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_UNREGISTER,
		(xdrproc_t) xdr_cms_register_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_enumerate_calendar_attr_res *
cms_enumerate_calendar_attr_5(cms_name *argp, _DtCm_Connection *clnt)
{
	static cms_enumerate_calendar_attr_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_ENUMERATE_CALENDAR_ATTR,
		(xdrproc_t) xdr_cms_name, (caddr_t) argp,
		(xdrproc_t) xdr_cms_enumerate_calendar_attr_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_get_cal_attr_res *
cms_get_calendar_attr_5(cms_get_cal_attr_args *argp, _DtCm_Connection *clnt)
{
	static cms_get_cal_attr_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_GET_CALENDAR_ATTR,
		(xdrproc_t) xdr_cms_get_cal_attr_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_get_cal_attr_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_set_calendar_attr_5(cms_set_cal_attr_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_SET_CALENDAR_ATTR,
		(xdrproc_t) xdr_cms_set_cal_attr_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_archive_res *
cms_archive_5(cms_archive_args *argp, _DtCm_Connection *clnt)
{
	static cms_archive_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_ARCHIVE,
		(xdrproc_t) xdr_cms_archive_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_archive_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_restore_5(cms_restore_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_RESTORE,
		(xdrproc_t) xdr_cms_restore_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_reminder_res *
cms_lookup_reminder_5(cms_reminder_args *argp, _DtCm_Connection *clnt)
{
	static cms_reminder_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_LOOKUP_REMINDER,
		(xdrproc_t) xdr_cms_reminder_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_reminder_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_entries_res *
cms_lookup_entries_5(cms_lookup_entries_args *argp, _DtCm_Connection *clnt)
{
	static cms_entries_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_LOOKUP_ENTRIES,
		(xdrproc_t) xdr_cms_lookup_entries_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_entries_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_entries_res *
cms_enumerate_sequence_5(cms_enumerate_args *argp, _DtCm_Connection *clnt)
{
	static cms_entries_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_ENUMERATE_SEQUENCE,
		(xdrproc_t) xdr_cms_enumerate_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_entries_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_get_entry_attr_res *
cms_get_entry_attr_5(cms_get_entry_attr_args *argp, _DtCm_Connection *clnt)
{
	static cms_get_entry_attr_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_GET_ENTRY_ATTR,
		(xdrproc_t) xdr_cms_get_entry_attr_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_get_entry_attr_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_entry_res *
cms_insert_entry_5(cms_insert_args *argp, _DtCm_Connection *clnt)
{
	static cms_entry_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_INSERT_ENTRY,
		(xdrproc_t) xdr_cms_insert_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_entry_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

cms_entry_res *
cms_update_entry_5(cms_update_args *argp, _DtCm_Connection *clnt)
{
	static cms_entry_res clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_UPDATE_ENTRY,
		(xdrproc_t) xdr_cms_update_args, (caddr_t) argp,
		(xdrproc_t) xdr_cms_entry_res, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

CSA_return_code *
cms_delete_entry_5(cms_delete_args *argp, _DtCm_Connection *clnt)
{
	static CSA_return_code clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (_DtCm_clnt_call (clnt, CMS_DELETE_ENTRY,
		(xdrproc_t) xdr_cms_delete_args, (caddr_t) argp,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
