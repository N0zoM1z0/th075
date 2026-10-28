// Borrowed global catalogs and authentic reference-count lifetime entry.
// No complete private archive list or owner layout is inferred here.
class ArchiveResourceRegistryF392 {public:void Clear();};
class ArchiveNameRegistryF392 {public:void Clear();};
extern unsigned int g_ArchiveUseCountAt0068BE04;
extern ArchiveResourceRegistryF392 g_ArchiveResourcesAt0068BE08;
extern ArchiveNameRegistryF392 g_ArchiveNamesAt0068BE1C;
class ArchiveCatalogF392 {public:ArchiveCatalogF392* BeginUse();};
ArchiveCatalogF392* ArchiveCatalogF392::BeginUse() {
    if (g_ArchiveUseCountAt0068BE04 == 0) {
        g_ArchiveResourcesAt0068BE08.Clear();
        g_ArchiveNamesAt0068BE1C.Clear();
    }
    ++g_ArchiveUseCountAt0068BE04;
    return this;
}
