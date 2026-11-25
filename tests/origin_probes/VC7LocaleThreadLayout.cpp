// Complete vendor CRT layouts; these do not declare any game owner.
#include <stddef.h>
#include <locale.h>
#include <mtdll.h>

extern "C" const unsigned long LocaleThreadLayoutProbe[] = {
    sizeof(_tiddata), offsetof(_tiddata, _errmsg), offsetof(_tiddata, _namebuf0),
    offsetof(_tiddata, _namebuf1), offsetof(_tiddata, _asctimebuf),
    offsetof(_tiddata, _gmtimebuf), offsetof(_tiddata, _cvtbuf),
    offsetof(_tiddata, _pxcptacttab), offsetof(_tiddata, ptmbcinfo), offsetof(_tiddata, ptlocinfo),
    sizeof(threadmbcinfo), offsetof(threadmbcinfo, refcount),
    offsetof(threadmbcinfo, mbcodepage), offsetof(threadmbcinfo, ismbcodepage),
    offsetof(threadmbcinfo, mblcid), offsetof(threadmbcinfo, mbulinfo),
    offsetof(threadmbcinfo, mbctype), offsetof(threadmbcinfo, mbcasemap),
    sizeof(threadlocinfo), offsetof(threadlocinfo, refcount),
    offsetof(threadlocinfo, lconv_intl_refcount), offsetof(threadlocinfo, lconv_num_refcount),
    offsetof(threadlocinfo, lconv_mon_refcount), offsetof(threadlocinfo, lconv),
    offsetof(threadlocinfo, lconv_intl), offsetof(threadlocinfo, ctype1_refcount),
    offsetof(threadlocinfo, ctype1), offsetof(threadlocinfo, pctype),
    offsetof(threadlocinfo, lc_time_curr), offsetof(threadlocinfo, lc_time_intl),
    sizeof(lconv), offsetof(lconv, decimal_point), offsetof(lconv, thousands_sep),
    offsetof(lconv, grouping), offsetof(lconv, int_curr_symbol), offsetof(lconv, currency_symbol),
    offsetof(lconv, mon_decimal_point), offsetof(lconv, mon_thousands_sep),
    offsetof(lconv, mon_grouping), offsetof(lconv, positive_sign), offsetof(lconv, negative_sign),
    sizeof(__lc_time_data), offsetof(__lc_time_data, wday_abbr), offsetof(__lc_time_data, wday),
    offsetof(__lc_time_data, month_abbr), offsetof(__lc_time_data, month),
    offsetof(__lc_time_data, ampm), offsetof(__lc_time_data, ww_sdatefmt),
    offsetof(__lc_time_data, ww_ldatefmt), offsetof(__lc_time_data, ww_timefmt),
    offsetof(__lc_time_data, ww_lcid), offsetof(__lc_time_data, ww_caltype),
    offsetof(__lc_time_data, refcount), sizeof(unsigned short), sizeof(void *)
};
