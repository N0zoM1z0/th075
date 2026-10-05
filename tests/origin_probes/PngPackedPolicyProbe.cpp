// Pointer-only free-function observations from complete original COFF symbols.
// The private PNG tags remain incomplete; no owner is instantiated or embedded.
#include <mmintrin.h>
#include <stddef.h>

namespace D3DX {
struct png_struct_def;
struct png_info_struct;
struct png_color_struct;
void __cdecl png_read_init(png_struct_def *);
void __cdecl png_read_rows(png_struct_def *, unsigned char **, unsigned char **, unsigned long);
void __cdecl png_read_end(png_struct_def *, png_info_struct *);
void __cdecl png_set_dither(png_struct_def *, png_color_struct *, int, int, unsigned short *, int);
void __cdecl MYCbCrA2RGBA(int, unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *);
void __cdecl MYCbCrA2RGBALegacy(int, unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *);
}

void ProbePngReadInit(D3DX::png_struct_def *state)
{
    D3DX::png_read_init(state);
}

void ProbePngReadRows(D3DX::png_struct_def *state, unsigned char **rows,
    unsigned char **display_rows, unsigned long count)
{
    D3DX::png_read_rows(state, rows, display_rows, count);
}

void ProbePngReadEnd(D3DX::png_struct_def *state, D3DX::png_info_struct *info)
{
    D3DX::png_read_end(state, info);
}

void ProbePngDither(D3DX::png_struct_def *state, D3DX::png_color_struct *palette,
    int colors, int maximum, unsigned short *histogram, int full)
{
    D3DX::png_set_dither(state, palette, colors, maximum, histogram, full);
}

void ProbeYcbcr(int count, unsigned char *first, unsigned char *second,
    unsigned char *third, unsigned char *fourth, unsigned char *fifth)
{
    D3DX::MYCbCrA2RGBA(count, first, second, third, fourth, fifth);
}

void ProbeYcbcrLegacy(int count, unsigned char *first, unsigned char *second,
    unsigned char *third, unsigned char *fourth, unsigned char *fifth)
{
    D3DX::MYCbCrA2RGBALegacy(count, first, second, third, fourth, fifth);
}

// Complete generic packed arithmetic controls; no target conversion body.
void ProbePackedCenter(__m64 *output, const __m64 *samples, const __m64 *center)
{
    *output = _mm_subs_pi16(*samples, *center);
    _mm_empty();
}

void ProbePackedDot(__m64 *output, const __m64 *samples, const __m64 *weights)
{
    *output = _mm_madd_pi16(*samples, *weights);
    _mm_empty();
}

void ProbePackedHalf(__m64 *output, const __m64 *samples)
{
    *output = _mm_srai_pi32(*samples, 1);
    _mm_empty();
}

void ProbePackedNarrow(__m64 *output, const __m64 *samples)
{
    __m64 low = _mm_packs_pi32(samples[0], samples[1]);
    __m64 high = _mm_packs_pi32(samples[2], samples[3]);
    *output = _mm_packs_pu16(low, high);
    _mm_empty();
}

void ProbePackedInterleave(__m64 *output, const __m64 *first, const __m64 *second)
{
    *output = _mm_unpacklo_pi8(*first, *second);
    _mm_empty();
}

void ProbePackedKeepState(__m64 *output, const __m64 *samples, const __m64 *center)
{
    *output = _mm_subs_pi16(*samples, *center);
}

extern const unsigned int PngPackedPublicLayout[] = {
    sizeof(__m64), sizeof(unsigned char), sizeof(unsigned short),
    sizeof(unsigned long), sizeof(int), sizeof(void *)
};
