
#include <ntddk.h>
#include <intrin.h> //__cpuid()

#define MAX_THREADS_PROCESSOR64 64

HANDLE hThreads[MAX_THREADS_PROCESSOR64] = { 0 };
PVOID ThreadObjects[MAX_THREADS_PROCESSOR64] = { 0 };
BOOLEAN signal = FALSE;
ULONG cpuNumbers = 0;

#define DELAY_ONE_MICROSECOND (-10)
#define DELAY_ONE_MILLISECOND (DELAY_ONE_MICROSECOND*1000)


VOID StartRoutine(IN PVOID CTX)
{
	GROUP_AFFINITY group={ 0 };
	ULONG index=0x19C; //0x19C is the value to access the register to obtain the value of the thermal sensor
	UINT64 readout = 0;
	ULONG delta = 0;
	ULONG CPUtemp = 0;
	LARGE_INTEGER interval = { 0 };

	KdPrint(("I'm here on startroutine"));

	interval.QuadPart = DELAY_ONE_MILLISECOND * 3000;

	group.Group = 0;
	group.Mask = (1 << (UINT64)CTX);

	KeSetSystemGroupAffinityThread(&group, NULL);

	while (1)
	{
		if (signal == TRUE)
			break;

		KdPrint(("I'm here on startroutine loop"));

		KeDelayExecutionThread(KernelMode, FALSE, &interval);

		readout= __readmsr(index);

	
			delta = (readout >> 16) & 0x7F;
			CPUtemp = 100 - delta;
			DbgPrint("CPU %d : temp is %d \r\n", CTX, CPUtemp);
		
	}

	PsTerminateSystemThread(STATUS_SUCCESS);
}
VOID DriverUnload(IN PDRIVER_OBJECT pDriverObject)
{
	KdPrint(("Driver unloaded succesfully \r\n"));
	signal = TRUE;

	for (int i = 0; i < cpuNumbers; i++)
	{
		if (ThreadObjects[i])
		{
			KdPrint(("Dereferencing thread no. %d", i));

			KeWaitForSingleObject(ThreadObjects[i], Executive, KernelMode, FALSE, NULL);

			ObDereferenceObject(ThreadObjects[i]);
		}
	}
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegistryPath)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	INT cpuinfo[4] = { 0 }; //it'll contain EAX,EBX,ECX, and EDX, to store the cpu informations (to see if actually it's an intel cpu etc..).
	ULONG cpuNumbers = 0;

	KdPrint(("Driver loaded succesfully \r\n"));
	pDriverObject->DriverUnload = DriverUnload;

	__cpuid(cpuinfo, 0);
	
	if (cpuinfo[1] != 0x756E6547 || cpuinfo[2] != 0x6C65746E || cpuinfo[3] != 0x49656E69)
	{
		DbgPrint("This CPU isn't Intel \r\n");
		return status;
	}
	
	__cpuid(cpuinfo, 1);
	
	if ((cpuinfo[3] & 0x20) == 0) //0x20 is bit n5 (in dec 32)
	{
		KdPrint(("RDMSR not supported"));
		return status;
	}

	__cpuid(cpuinfo, 6);

	if ((cpuinfo[0] & 1) == 0) //BIT 0 is digital thermal sensor, we're checking if with an and operation it's equal to 1 or not
	{
		KdPrint(("Digital thermal not supported"));
		return status;
	}
	
	cpuNumbers = KeQueryActiveProcessorCountEx(0);

	KdPrint(("There are: %ul\r\n", cpuNumbers));

	int i = 0;
	KdPrint(("I'm here now"));

	for (i = 0; i<cpuNumbers; i++)
	{
		KdPrint(("Loop finished"));
		status = PsCreateSystemThread(&hThreads[i], 0, NULL, NULL, NULL, StartRoutine, (PVOID)i);

		if (!NT_SUCCESS(status))
		{
			KdPrint(("Failed to create the thread no. %d \r\n", i));
			break;
		}

		status = ObReferenceObjectByHandle(hThreads[i], THREAD_ALL_ACCESS, NULL, KernelMode, &ThreadObjects[i], NULL);

		if (!NT_SUCCESS(status))
		{
			KdPrint(("Failed to reference the thread no. %d \r\n", i));
			break;
		}
		ZwClose(hThreads[i]);
	}

	KdPrint(("Loop finished"));

	status = STATUS_SUCCESS;

	return status;
}