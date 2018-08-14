#include "Major Functions.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING RegistryPath)
{
	NTSTATUS Status = STATUS_SUCCESS;

	//Initialization of global strings.
	RtlInitUnicodeString(&DeviceName, L"\\Device\\ASM Process Info Service");
	RtlInitUnicodeString(&SymbolicLinkName, L"\\??\\ASM Process Link");

	//Create a device used by the driver.
	Status = IoCreateDevice(pDriverObject, 0, &DeviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	if (!NT_SUCCESS(Status))
	{
		KdPrint(("Unable to create device\r\n"));
		return Status;
	}

	//Sets up a symbolic link between a device object name and a user-visible name for the device.
	Status = IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	if (!NT_SUCCESS(Status))
	{
		KdPrint(("Unable to create symbolic link\r\n"));
		IoDeleteDevice(pDeviceObject);
		return Status;
	}

	//Set up driver options and major fuctions
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->DriverUnload = UnloadDriver;

	return Status;
}