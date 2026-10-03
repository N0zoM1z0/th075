// Natural vendor/SDK layouts used by the complete codepage and NLS graph.
#include <stddef.h>
#include <windows.h>
#include <locale.h>
#include <mtdll.h>

// The private mbctype.c record declaration uses six USHORTs and four ranges.
struct CodePageRecordLayout {
    int code_page;
    unsigned short mbulinfo[6];
    unsigned char rgrange[4][8];
};
extern "C" const unsigned long CodePageLayoutProbe[] = {
    sizeof(CPINFO), offsetof(CPINFO, MaxCharSize), offsetof(CPINFO, DefaultChar),
    offsetof(CPINFO, LeadByte), sizeof(((CPINFO *)0)->LeadByte),
    sizeof(MEMORY_BASIC_INFORMATION), offsetof(MEMORY_BASIC_INFORMATION, BaseAddress),
    offsetof(MEMORY_BASIC_INFORMATION, AllocationBase), offsetof(MEMORY_BASIC_INFORMATION, RegionSize),
    offsetof(MEMORY_BASIC_INFORMATION, State), offsetof(MEMORY_BASIC_INFORMATION, Protect),
    sizeof(SYSTEM_INFO), offsetof(SYSTEM_INFO, dwPageSize),
    sizeof(CodePageRecordLayout), offsetof(CodePageRecordLayout, mbulinfo),
    offsetof(CodePageRecordLayout, rgrange), sizeof(CodePageRecordLayout[5]),
    sizeof(threadmbcinfo), offsetof(threadmbcinfo, mbulinfo),
    sizeof(((threadmbcinfo *)0)->mbulinfo), offsetof(threadmbcinfo, mbctype),
    offsetof(threadmbcinfo, mbcasemap), sizeof(threadlocinfo),
    offsetof(threadlocinfo, lc_codepage), offsetof(threadlocinfo, lc_handle),
    offsetof(threadlocinfo, mb_cur_max), offsetof(threadlocinfo, pctype),
    CT_CTYPE1, LCMAP_LOWERCASE, LCMAP_UPPERCASE, LCMAP_SORTKEY,
    MB_PRECOMPOSED, MB_ERR_INVALID_CHARS, LOCALE_IDEFAULTANSICODEPAGE,
    ERROR_CALL_NOT_IMPLEMENTED, MEM_COMMIT, PAGE_READWRITE, PAGE_GUARD, PAGE_NOACCESS,
    VER_PLATFORM_WIN32_WINDOWS, sizeof(wchar_t), sizeof(unsigned short), sizeof(void *)
};
