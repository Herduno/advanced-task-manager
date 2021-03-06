// Driver Test.cpp: definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <string>

#include <devioctl.h>

//Pre-Processors driver control codes
#define GET_PID_LIST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

using namespace std;

wstring Path = L"C:\\Users\\Test\\Desktop\\ProcessInfo.sys";
wstring Name = L"ProcessInfo.sys";
wstring Link = L"\\\\.\\ASM Process Link";

HANDLE OpenDriver(LPCWSTR DriverName)
{
	return CreateFileW(DriverName, GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
}

typedef struct _PID_LIST
{
	PULONG Pid;
	SIZE_T nPid;
}PID_LIST, *PPID_LIST, *LPPID_LIST;

int main()
{
	bool Scelta;
	
	cout << "1)Path\n2)Name\n3)Link\n\n";
	cin >> Scelta;

	HANDLE hDriver;

	if (Scelta == 1)  hDriver = CreateFileW(Path.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
	else if(Scelta == 2) hDriver = CreateFileW(Name.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
	else hDriver = CreateFileW(Link.c_str(), GENERIC_ALL, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);


	if (hDriver == INVALID_HANDLE_VALUE)
	{
		cout << "Can't find Driver\n";
		cout << GetLastError() << endl;
	}

	PID_LIST a;

	if (!DeviceIoControl(hDriver, GET_PID_LIST, &a, sizeof(a), &a, sizeof(a), 0, 0))
	{
		cout << "IoCtrl Failed\n";
		cout << GetLastError() << endl;
	}

	system("PAUSE");
	return 0;
}