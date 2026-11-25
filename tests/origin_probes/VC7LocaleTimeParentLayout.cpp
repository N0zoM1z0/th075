// Complete pinned CRT/SDK layouts and natural locale/time call contracts.
#include <stddef.h>
#include <time.h>
#include <locale.h>
#include <mtdll.h>
#include <setlocal.h>

// strftime.c defines these private selectors for its localized format worker.
enum { TimeShortDateControl = 0, TimeLongDateControl = 1, TimeClockControl = 2 };

extern "C" const unsigned long LocaleTimeParentLayoutProbe[] = {
    sizeof(void *), sizeof(size_t), sizeof(int), sizeof(BOOL), sizeof(WORD),
    sizeof(struct tm), offsetof(struct tm, tm_sec), offsetof(struct tm, tm_min),
    offsetof(struct tm, tm_hour), offsetof(struct tm, tm_mday), offsetof(struct tm, tm_mon),
    offsetof(struct tm, tm_year), offsetof(struct tm, tm_wday), offsetof(struct tm, tm_yday),
    offsetof(struct tm, tm_isdst), sizeof(SYSTEMTIME), offsetof(SYSTEMTIME, wYear),
    offsetof(SYSTEMTIME, wMonth), offsetof(SYSTEMTIME, wDayOfWeek), offsetof(SYSTEMTIME, wDay),
    offsetof(SYSTEMTIME, wHour), offsetof(SYSTEMTIME, wMinute), offsetof(SYSTEMTIME, wSecond),
    offsetof(SYSTEMTIME, wMilliseconds), sizeof(threadlocinfo), offsetof(threadlocinfo, refcount),
    offsetof(threadlocinfo, lc_codepage), offsetof(threadlocinfo, lc_collate_cp),
    offsetof(threadlocinfo, lc_handle), sizeof(((threadlocinfo *)0)->lc_handle),
    offsetof(threadlocinfo, lc_clike), offsetof(threadlocinfo, mb_cur_max),
    offsetof(threadlocinfo, lconv_intl_refcount), offsetof(threadlocinfo, lconv_num_refcount),
    offsetof(threadlocinfo, lconv_mon_refcount), offsetof(threadlocinfo, lconv),
    offsetof(threadlocinfo, lconv_intl), offsetof(threadlocinfo, ctype1_refcount),
    offsetof(threadlocinfo, ctype1), offsetof(threadlocinfo, pctype),
    offsetof(threadlocinfo, lc_time_curr), offsetof(threadlocinfo, lc_time_intl),
    sizeof(_tiddata), offsetof(_tiddata, ptlocinfo), sizeof(struct __lc_time_data),
    offsetof(struct __lc_time_data, wday_abbr), offsetof(struct __lc_time_data, wday),
    offsetof(struct __lc_time_data, month_abbr), offsetof(struct __lc_time_data, month),
    offsetof(struct __lc_time_data, ampm), offsetof(struct __lc_time_data, ww_sdatefmt),
    offsetof(struct __lc_time_data, ww_ldatefmt), offsetof(struct __lc_time_data, ww_timefmt),
    offsetof(struct __lc_time_data, ww_lcid), offsetof(struct __lc_time_data, ww_caltype),
    offsetof(struct __lc_time_data, refcount), LC_MIN, LC_MAX, LC_ALL, MAX_LC_LEN,
    _SETLOCALE_LOCK, TimeShortDateControl, TimeLongDateControl, TimeClockControl,
    EXCEPTION_EXECUTE_HANDLER
};

extern "C" char *LocaleParentCallControl(char *(*worker)(int, const char *),
                                         int category, const char *locale) {
    return worker(category, locale);
}
extern "C" size_t TimeFormatCallControl(
    size_t (*worker)(pthreadlocinfo, char *, size_t, const char *, const struct tm *, void *),
    pthreadlocinfo locale, char *output, size_t capacity, const char *format,
    const struct tm *time, void *time_locale) {
    return worker(locale, output, capacity, format, time, time_locale);
}
extern "C" BOOL TimeExpandCallControl(
    BOOL (*worker)(pthreadlocinfo, char, const struct tm *, char **, size_t *,
                   struct __lc_time_data *, unsigned),
    pthreadlocinfo locale, char specifier, const struct tm *time, char **output,
    size_t *remaining, struct __lc_time_data *time_locale, unsigned alternate) {
    return worker(locale, specifier, time, output, remaining, time_locale, alternate);
}
extern "C" int TimeApiCallControl(int field, LCID locale, const SYSTEMTIME *time,
                                  LPCSTR format, LPSTR output, int capacity) {
    int (WINAPI *formatter)(LCID, DWORD, const SYSTEMTIME *, LPCSTR, LPSTR, int);
    formatter = field == TimeClockControl ? GetTimeFormatA : GetDateFormatA;
    return formatter(locale, 0, time, format, output, capacity);
}
