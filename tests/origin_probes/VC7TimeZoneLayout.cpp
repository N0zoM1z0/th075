// Complete CRT/SDK time and thread types; synthetic transition layout control.
#include <stddef.h>
#include <windows.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <cruntime.h>
#include <ctime.h>
#include <mtdll.h>

struct DSTTransitionLayoutControl {
    int year;
    int year_day;
    int milliseconds;
};

extern "C" const unsigned long TimeZoneLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(long), sizeof(time_t), sizeof(wchar_t),
    sizeof(tm), offsetof(tm, tm_sec), offsetof(tm, tm_min), offsetof(tm, tm_hour),
    offsetof(tm, tm_mday), offsetof(tm, tm_mon), offsetof(tm, tm_year),
    offsetof(tm, tm_wday), offsetof(tm, tm_yday), offsetof(tm, tm_isdst),
    sizeof(_tiddata), offsetof(_tiddata, _gmtimebuf), offsetof(_tiddata, ptmbcinfo),
    sizeof(threadmbcinfo), offsetof(threadmbcinfo, mbcodepage),
    offsetof(threadmbcinfo, ismbcodepage), offsetof(threadmbcinfo, mblcid),
    offsetof(threadmbcinfo, mbctype),
    sizeof(SYSTEMTIME), offsetof(SYSTEMTIME, wYear), offsetof(SYSTEMTIME, wMonth),
    offsetof(SYSTEMTIME, wDayOfWeek), offsetof(SYSTEMTIME, wDay),
    offsetof(SYSTEMTIME, wHour), offsetof(SYSTEMTIME, wMinute),
    offsetof(SYSTEMTIME, wSecond), offsetof(SYSTEMTIME, wMilliseconds),
    sizeof(TIME_ZONE_INFORMATION), offsetof(TIME_ZONE_INFORMATION, Bias),
    offsetof(TIME_ZONE_INFORMATION, StandardName), offsetof(TIME_ZONE_INFORMATION, StandardDate),
    offsetof(TIME_ZONE_INFORMATION, StandardBias), offsetof(TIME_ZONE_INFORMATION, DaylightName),
    offsetof(TIME_ZONE_INFORMATION, DaylightDate), offsetof(TIME_ZONE_INFORMATION, DaylightBias),
    sizeof(DSTTransitionLayoutControl), offsetof(DSTTransitionLayoutControl, year),
    offsetof(DSTTransitionLayoutControl, year_day), offsetof(DSTTransitionLayoutControl, milliseconds),
    _TIME_LOCK, _ENV_LOCK, _DAY_SEC, _YEAR_SEC, _FOUR_YEAR_SEC,
    LONG_MAX, 3 * _DAY_SEC, LONG_MAX - 3 * _DAY_SEC, NORM_IGNORECASE
};

extern "C" char *NarrowDupCallControl(const char *text) {
    return _strdup(text);
}
extern "C" wchar_t *WideDupCallControl(const wchar_t *text) {
    return _wcsdup(text);
}
