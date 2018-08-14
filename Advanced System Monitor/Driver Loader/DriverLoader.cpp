#include "DriverLoader.h"


RETURN_STATUS DRIVER_LOADER_DLL_API CreateDriverService(_In_ LPCWSTR szDriverName, _Out_opt_ SC_HANDLE* lpServiceHandle)
{
	SC_HANDLE hManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!hManager) return GetLastError();

	WCHAR FullDriverPath[MAX_PATH];
	GetFullPathNameW(szDriverName, MAX_PATH, FullDriverPath, NULL);

	SC_HANDLE hService = CreateServiceW(hManager, szDriverName, L"Advanced Task Manager Service", SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, FullDriverPath, NULL, NULL, NULL, NULL, NULL);
	if (!hService) return GetLastError();

	if (lpServiceHandle) *lpServiceHandle = hService;

	return true;
}

RETURN_STATUS DRIVER_LOADER_DLL_API UnloadDriverService(_In_ LPCWSTR szDriverName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!hSCManager) return GetLastError();

	SC_HANDLE hService = OpenServiceW(hSCManager, szDriverName, SERVICE_ALL_ACCESS);
	if (!hService) 
	{
		CloseServiceHandle(hSCManager);
		return GetLastError();
	}

	DeleteService(hService);
	CloseServiceHandle(hSCManager);

	return true;
}

RETURN_STATUS DRIVER_LOADER_DLL_API StartDriverService(_In_ LPCWSTR szDriverName)
{
	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!hSCManager) return GetLastError();

	SC_HANDLE hService = OpenServiceW(hSCManager, szDriverName, SERVICE_ALL_ACCESS);
	if (!hService) 
	{
		CloseServiceHandle(hSCManager);
		return GetLastError();
	}

	if (!StartService(hService, 0, NULL)) 
	{
		CloseServiceHandle(hSCManager);
		CloseServiceHandle(hService);
		return GetLastError();
	}

	CloseServiceHandle(hSCManager);
	return true;
}

RETURN_STATUS DRIVER_LOADER_DLL_API StopDriverService(_In_ LPCWSTR szDriverName, _Out_opt_ SERVICE_STATUS* lpServiceStatus)
{
	SERVICE_STATUS ss;

	SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!hSCManager) return GetLastError();

	SC_HANDLE hService = OpenServiceW(hSCManager, szDriverName, SERVICE_ALL_ACCESS);
	if (!hService) 
	{
		CloseServiceHandle(hSCManager);
		return GetLastError();
	}

	if (!ControlService(hService, SERVICE_CONTROL_STOP, &ss)) 
	{
		CloseServiceHandle(hSCManager);
		CloseServiceHandle(hService);
		return GetLastError();

	}

	if (lpServiceStatus) *lpServiceStatus = ss;

	CloseServiceHandle(hSCManager);
	CloseServiceHandle(hService);
	return true;
}