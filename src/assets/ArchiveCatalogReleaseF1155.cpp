#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"

ArchiveCatalog::~ArchiveCatalog() {
    if (--g_ArchiveUseCountAt0068BE04 == 0) {
        for (unsigned int index=0; index<g_ArchiveNamesAt0068BE1C.size(); ++index) {
            delete g_ArchiveObjectsAt0068BE08[index];
            // OpenAndRegister allocates each registered name with new char[].
            delete[] g_ArchiveNamesAt0068BE1C[index];
        }
        g_ArchiveObjectsAt0068BE08.clear();
        g_ArchiveNamesAt0068BE1C.clear();
    }
}
