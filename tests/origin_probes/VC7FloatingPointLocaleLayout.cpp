// Complete locale fields used by the FP conversion character helpers.
#include <stddef.h>
#include <locale.h>
#include <mtdll.h>
extern "C" const unsigned long FloatingPointLocaleLayoutProbe[] = {
    sizeof(threadlocinfo), offsetof(threadlocinfo, lc_codepage),
    offsetof(threadlocinfo, lc_handle), sizeof(((threadlocinfo *)0)->lc_handle),
    offsetof(threadlocinfo, mb_cur_max), offsetof(threadlocinfo, pctype),
    offsetof(threadlocinfo, lc_clike), sizeof(unsigned short), sizeof(void *),
    sizeof(DWORD), PF_FLOATING_POINT_PRECISION_ERRATA, sizeof(BOOL), sizeof(&IsProcessorFeaturePresent)
};
