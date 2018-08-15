#if !defined(_MAJOR_FUNCTION_INCLUDED_)

#define _MAJOR_FUNCTION_INCLUDED_

#include "Objects.h"

NTSTATUS CreateCall(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	DbgPrint("Call Created\r\n");
	
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT pDeviceObject, PIRP pIrp)
{
	DbgPrint("Call Closed\r\n");
	
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

VOID UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Unload device\r\n");
	
	IoDeleteSymbolicLink(&SymbolicLinkName);
	IoDeleteDevice(pDeviceObject);
}

#endif