#include "ArchiveCatalog.hpp"

class ArchiveCatalogF392 {public:ArchiveCatalogF392* BeginUse();};
ArchiveCatalogF392* ArchiveCatalogF392::BeginUse() {
    if (g_ArchiveUseCountAt0068BE04 == 0) {
        g_ArchiveObjectsAt0068BE08.clear();
        g_ArchiveNamesAt0068BE1C.clear();
    }
    ++g_ArchiveUseCountAt0068BE04;
    return this;
}
