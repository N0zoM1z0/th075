// SDK layout and flag controls for the CRT's dynamic window-station query.
#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <stddef.h>
extern "C" const unsigned long UserObjectLayoutProbe[6] = {
    sizeof(USEROBJECTFLAGS), offsetof(USEROBJECTFLAGS, dwFlags),
    WSF_VISIBLE, UOI_FLAGS,
    MB_SERVICE_NOTIFICATION, MB_SERVICE_NOTIFICATION_NT3X
};
