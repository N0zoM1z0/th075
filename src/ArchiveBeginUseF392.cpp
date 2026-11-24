#include "ArchiveCatalog.hpp"

ArchiveCatalog::ArchiveCatalog() {
    if (g_ArchiveUseCountAt0068BE04 == 0) {
        g_ArchiveObjectsAt0068BE08.clear();
        g_ArchiveNamesAt0068BE1C.clear();
    }
    ++g_ArchiveUseCountAt0068BE04;
}
