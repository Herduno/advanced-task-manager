#if !defined(_DRIVER_OBJECT_INCLUDED_)

#define _DRIVER_OBJECT_INCLUDED_

#include "ntf.h"

PDEVICE_OBJECT pDeviceObject = NULL;       //Object device to perform communications with the application
UNICODE_STRING DeviceName;                 //Name with which to identify the object device
UNICODE_STRING SymbolicLinkName;           //Name of the symbolic link to connect with the driver


/* TYPE DEFINITIONS */
typedef struct _PID_LIST
{
	PULONG Pid;
	SIZE_T nPid;
}PID_LIST, *PPID_LIST, *LPPID_LIST;

#endif
