// Complete vendor thread/locale layouts, in their SDK-compatible header context.
#include <stddef.h>
#include <locale.h>
#include <mtdll.h>
extern "C" const unsigned long OutputFormatLocaleLayoutProbe[] = {
    sizeof(void *), sizeof(wchar_t), sizeof(_tiddata), offsetof(_tiddata, ptlocinfo),
    sizeof(threadlocinfo), offsetof(threadlocinfo, lc_codepage),
    offsetof(threadlocinfo, lc_handle), sizeof(((threadlocinfo *)0)->lc_handle),
    offsetof(threadlocinfo, mb_cur_max), offsetof(threadlocinfo, pctype), LC_CTYPE,
    sizeof(DWORD), sizeof(BOOL)
};
