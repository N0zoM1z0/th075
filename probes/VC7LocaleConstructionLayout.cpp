// Complete SDK/CRT layouts and source-local locale record models.
#include <stddef.h>
#include <locale.h>
#include <mtdll.h>
#include <setlocal.h>
#include <ctype.h>
#include <limits.h>

struct LocaleCategoryLayoutControl {
    const char *name;
    char *locale;
    int (*initialize)(void);
};
struct LocaleNameLayoutControl {
    CHAR *name;
    CHAR abbreviation[4];
};
struct LocaleInfoLayoutControl {
    LCID locale;
    char language_id[8];
    char *language;
    char language_abbreviation[4];
    char *country;
    char country_abbreviation[4];
    char oem_codepage[8];
    char ansi_codepage[8];
};
struct LocaleCompatibilityLayoutControl {
    unsigned long codepage;
    int compatible;
};
// initctyp.c defines the private classification entry count as 257.
enum { LocaleCTypeEntriesControl = 257 };

extern "C" const unsigned long LocaleConstructionLayoutProbe[] = {
    sizeof(void *), sizeof(int), sizeof(WORD), sizeof(DWORD), sizeof(BOOL), sizeof(LCID),
    sizeof(LC_ID), offsetof(LC_ID, wLanguage), offsetof(LC_ID, wCountry),
    offsetof(LC_ID, wCodePage), sizeof(LC_STRINGS), offsetof(LC_STRINGS, szLanguage),
    offsetof(LC_STRINGS, szCountry), offsetof(LC_STRINGS, szCodePage),
    MAX_LANG_LEN, MAX_CTRY_LEN, MAX_CP_LEN, MAX_LC_LEN,
    sizeof(LocaleCategoryLayoutControl), offsetof(LocaleCategoryLayoutControl, name),
    offsetof(LocaleCategoryLayoutControl, locale), offsetof(LocaleCategoryLayoutControl, initialize),
    sizeof(LocaleCategoryLayoutControl[6]), LC_ALL, LC_COLLATE, LC_CTYPE,
    LC_MONETARY, LC_NUMERIC, LC_TIME, LC_MIN, LC_MAX,
    sizeof(LocaleCompatibilityLayoutControl), sizeof(LocaleCompatibilityLayoutControl[5]),
    sizeof(LocaleNameLayoutControl), offsetof(LocaleNameLayoutControl, abbreviation),
    sizeof(LocaleInfoLayoutControl), offsetof(LocaleInfoLayoutControl, language_id),
    offsetof(LocaleInfoLayoutControl, language), offsetof(LocaleInfoLayoutControl, language_abbreviation),
    offsetof(LocaleInfoLayoutControl, country), offsetof(LocaleInfoLayoutControl, country_abbreviation),
    offsetof(LocaleInfoLayoutControl, oem_codepage), offsetof(LocaleInfoLayoutControl, ansi_codepage),
    sizeof(struct lconv), offsetof(struct lconv, grouping), offsetof(struct lconv, mon_grouping),
    offsetof(struct lconv, int_frac_digits), offsetof(struct lconv, n_sign_posn),
    sizeof(struct __lc_time_data), offsetof(struct __lc_time_data, wday),
    offsetof(struct __lc_time_data, month_abbr), offsetof(struct __lc_time_data, month),
    offsetof(struct __lc_time_data, ampm), offsetof(struct __lc_time_data, ww_sdatefmt),
    offsetof(struct __lc_time_data, ww_ldatefmt), offsetof(struct __lc_time_data, ww_timefmt),
    offsetof(struct __lc_time_data, ww_lcid), offsetof(struct __lc_time_data, ww_caltype),
    offsetof(struct __lc_time_data, refcount), sizeof(threadlocinfo),
    sizeof(CPINFO), offsetof(CPINFO, MaxCharSize), offsetof(CPINFO, DefaultChar),
    offsetof(CPINFO, LeadByte), sizeof(((CPINFO *)0)->LeadByte), MB_LEN_MAX,
    LocaleCTypeEntriesControl, _COFFSET,
    (_COFFSET + LocaleCTypeEntriesControl) * sizeof(unsigned short),
    _COFFSET * sizeof(unsigned short), _LEADBYTE, CT_CTYPE1, LCID_INSTALLED,
    VER_PLATFORM_WIN32_NT, LOCALE_SENGLANGUAGE, LOCALE_SENGCOUNTRY,
    LOCALE_SABBREVLANGNAME, LOCALE_SABBREVCTRYNAME, LOCALE_IDEFAULTCODEPAGE,
    LOCALE_IDEFAULTANSICODEPAGE, sizeof(LOCALE_ENUMPROCA),
    LC_STR_TYPE, LC_INT_TYPE, sizeof(unsigned short[128]), sizeof(char[127])
};

extern "C" BOOL __stdcall LocaleEnumCallbackControl(LPSTR text) {
    return text && *text;
}
extern "C" BOOL LocaleEnumRegisterControl(LOCALE_ENUMPROCA callback) {
    return EnumSystemLocalesA(callback, LCID_INSTALLED);
}
extern "C" int LocaleCategoryInitControl(int (*initialize)(void)) {
    return initialize();
}
extern "C" int LocaleQuerySlotControl(int (__stdcall *query)(LCID, LCTYPE, LPSTR, int),
                                      LCID locale, LCTYPE field, LPSTR text, int count) {
    return query(locale, field, text, count);
}
