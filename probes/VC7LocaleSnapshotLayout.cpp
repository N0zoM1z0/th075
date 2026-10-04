// Complete CRT locale/time types and natural classification/copy controls.
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <mtdll.h>
#include <setlocal.h>
#include <ctype.h>

extern "C" const unsigned long LocaleSnapshotLayoutProbe[] = {
    sizeof(void *), sizeof(size_t), sizeof(int), sizeof(unsigned short),
    sizeof(struct __lc_time_data), offsetof(struct __lc_time_data, wday_abbr),
    sizeof(((struct __lc_time_data *)0)->wday_abbr) / sizeof(char *),
    offsetof(struct __lc_time_data, wday), sizeof(((struct __lc_time_data *)0)->wday) / sizeof(char *),
    offsetof(struct __lc_time_data, month_abbr),
    sizeof(((struct __lc_time_data *)0)->month_abbr) / sizeof(char *),
    offsetof(struct __lc_time_data, month), sizeof(((struct __lc_time_data *)0)->month) / sizeof(char *),
    offsetof(struct __lc_time_data, ampm), sizeof(((struct __lc_time_data *)0)->ampm) / sizeof(char *),
    offsetof(struct __lc_time_data, ww_sdatefmt), offsetof(struct __lc_time_data, ww_ldatefmt),
    offsetof(struct __lc_time_data, ww_timefmt), offsetof(struct __lc_time_data, ww_lcid),
    offsetof(struct __lc_time_data, ww_caltype), offsetof(struct __lc_time_data, refcount),
    offsetof(struct __lc_time_data, ww_lcid) / sizeof(char *), sizeof(threadlocinfo),
    offsetof(threadlocinfo, mb_cur_max), offsetof(threadlocinfo, pctype),
    sizeof(_tiddata), offsetof(_tiddata, ptlocinfo), _ALPHA, _ALPHA | _DIGIT,
    _UPPER, _LOWER, _DIGIT, (unsigned long)EOF
};

extern "C" void *TimeSnapshotCopyControl(void *destination, const void *source) {
    return memcpy(destination, source, sizeof(struct __lc_time_data));
}
extern "C" int SnapshotAlphabetControl(pthreadlocinfo locale, int character) {
    return __isalpha_mt(locale, character);
}
extern "C" int SnapshotAlnumControl(pthreadlocinfo locale, int character) {
    return __isalnum_mt(locale, character);
}
