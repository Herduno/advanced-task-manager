#if !defined(_PROCESS_CONTROL_CODES_DEFINED_ )

#include <devioctl.h>

//Pre-Processors driver control codes
#define GET_PID_LIST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

#endif