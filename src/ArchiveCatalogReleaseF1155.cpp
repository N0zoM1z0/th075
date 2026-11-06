#include <new>

// Borrowed interfaces to the two native registries and resource lifetime.
// These declarations do not establish complete private owner layouts.
class ArchiveResourceF343 { public: ~ArchiveResourceF343(); };
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
class ArchiveCatalogF343 { public: ~ArchiveCatalogF343(); };

ArchiveCatalogF343::~ArchiveCatalogF343() {
    if (--g_ArchiveUseCountAt0068BE04 == 0) {
        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.Size(); ++index) {
            delete *g_ArchiveResourcesAt0068BE08.At(index);
            // OpenAndRegister allocates each registered name with new char[].
            delete[] *g_ArchiveNamesAt0068BE1C.At(index);
        }
        g_ArchiveResourcesAt0068BE08.Clear();
        g_ArchiveNamesAt0068BE1C.Clear();
    }
}
