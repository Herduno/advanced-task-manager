#if !defined(_DRIVER_LOADER_INCLUDED_)

#define _DRIVER_LOADER_INCLUDED_

#include <Windows.h>

#if !defined(DRIVER_LOADER_DLL_IMPORT)
   #define DRIVER_LOADER_DLL_API __declspec(dllexport) __stdcall
#else
   #define DRIVER_LOADER_DLL_API __declspec(dllimport) __stdcall
#endif

#if !defined(FUNCTIONS_RETURN_STATUS)

#define FUNCTIONS_RETURN_STATUS

//Macro used to check if a function had success or not, the x value should be a RETURN_STATUS type.
#define FUNCTION_SUCCESS(x) (x != 1 ? false : true)
typedef DWORD RETURN_STATUS;

#endif

/* CreateDriverService: Create a service for registering a driver */
/* PARAMETERS */
// szDriverName:            A null terminated string indicating the name of the driver to register.
// lpServiceHandle:         A pointer to get the handle of the created service. This parameter can be NULL.
RETURN_STATUS DRIVER_LOADER_DLL_API CreateDriverService(_In_ LPCWSTR szDriverName, _Out_opt_ SC_HANDLE* lpServiceHandle);



/* UnloadDriverService: Delete the service of an existing driver */
/* PARAMETERS: */
// szDriverName:            A null terminated string indicating the name of the driver to unload.
RETURN_STATUS DRIVER_LOADER_DLL_API UnloadDriverService(_In_ LPCWSTR szDriverName);



/* UnloadDriverService: starts the service of a registered driver */
/* PARAMETERS: */
// szDriverName:            A null terminated string indicating the name of the driver to start.
RETURN_STATUS DRIVER_LOADER_DLL_API StartDriverService(_In_ LPCWSTR szDriverName);



/* UnloadDriverService: stop the service of a running registered driver */
/* PARAMETERS: */
// szDriverName:            A null terminated string indicating the name of the driver to stop.
// lpServiceStatus:         A pointer to the structure containing information about driver shutdown.
RETURN_STATUS DRIVER_LOADER_DLL_API StopDriverService(_In_ LPCWSTR szDriverName, _Out_opt_ SERVICE_STATUS* lpServiceStatus);


#endif