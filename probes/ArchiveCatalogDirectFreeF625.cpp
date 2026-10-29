// F625 complete original 0041CE50 171B/51-x86 authored destructor
// negative-source control. Natural direct free retains the real two
// original resource/delete EBP slots but emits 165B/49-x86, so this
// is NOT an accepted full original function or synthetic padding fix.
// F584: small original 0041CE50 whole ArchiveCatalog destructor source-only
// ORIGINAL Japanese TH075 1.11 171 CODE bytes, 51 x86 instructions.
// THIS IS A NONEXACT C++ PROBE, not an adopted original function.
// Direct pointer destruction and filename release are original-backed;
// existing VC7.1 C++ stack slot ownership is NOT original byte-exact.
// This file is input for targeted negative delete-expression controls.
// No byte graft, inline asm, fake padding, or independent CODE credit.
#include <stdlib.h>
// Only the native borrowed list and pointee interfaces, not their layouts.
class ArchiveResourceF343 {public: ~ArchiveResourceF343();};
class ArchiveResourcesF343 {
public:
    ArchiveResourceF343** At(unsigned int index);
    void Clear();
};
class ArchiveNamesF343 {
public:
    unsigned int Size();
    char** At(unsigned int index);
    void Clear();
};
extern unsigned int g_ArchiveUseCountAt0068BE04;
extern ArchiveResourcesF343 g_ArchiveResourcesAt0068BE08;
extern ArchiveNamesF343 g_ArchiveNamesAt0068BE1C;
class ArchiveCatalogF343 {public: ~ArchiveCatalogF343();};
ArchiveCatalogF343::~ArchiveCatalogF343() {
    if (--g_ArchiveUseCountAt0068BE04 == 0) {
        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            // Genuine pointer owner is freed directly; no invented local.
            free(*g_ArchiveNamesAt0068BE1C.At(index));
        }
        g_ArchiveResourcesAt0068BE08.Clear();
        g_ArchiveNamesAt0068BE1C.Clear();
    }
}
