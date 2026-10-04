// Complete SDK-compatible locale types and the real multibyte API declaration.
#include <stddef.h>
#include <locale.h>
#include <mtdll.h>
#include <setlocal.h>
#include <awint.h>
#include <errno.h>

extern "C" const unsigned long InputLocaleLayoutProbe[] = {
    sizeof(void *), sizeof(wchar_t), sizeof(_tiddata), offsetof(_tiddata, ptlocinfo),
    sizeof(threadlocinfo), offsetof(threadlocinfo, lc_codepage),
    offsetof(threadlocinfo, lc_handle), sizeof(((threadlocinfo *)0)->lc_handle),
    offsetof(threadlocinfo, mb_cur_max), offsetof(threadlocinfo, pctype), LC_CTYPE,
    sizeof(DWORD), sizeof(BOOL), sizeof(LCID), sizeof(LCTYPE), sizeof(UINT),
    MB_PRECOMPOSED, MB_ERR_INVALID_CHARS, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
    EILSEQ, LC_STR_TYPE, LC_INT_TYPE, ERROR_INSUFFICIENT_BUFFER,
    ERROR_CALL_NOT_IMPLEMENTED, LOCALE_ILANGUAGE, EXCEPTION_EXECUTE_HANDLER,
    sizeof(wchar_t[4]), sizeof(unsigned char[128])
};

extern "C" int InputWideCallControl(pthreadlocinfo locale, wchar_t *destination,
                                    const char *source, int count) {
    return MultiByteToWideChar(locale->lc_codepage,
                              MB_PRECOMPOSED | MB_ERR_INVALID_CHARS,
                              source, count, destination, destination ? 1 : 0);
}
