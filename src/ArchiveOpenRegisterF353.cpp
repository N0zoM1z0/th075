#include "ArchiveCatalog.hpp"
#include "DataArchive.hpp"
#include <string.h>

namespace ArchiveCatalogF353 {
void OpenAndRegister(const char* archiveFilename, const char* registeredName) {
    DataArchiveF481* emptyArchive=0;
    g_ArchiveObjectsAt0068BE08.push_back(emptyArchive);
    g_ArchiveObjectsAt0068BE08.back()=new DataArchiveF481();
    (g_ArchiveObjectsAt0068BE08.back())->OpenAndReadIndex(archiveFilename);
    g_ArchiveNamesAt0068BE1C.push_back(static_cast<char*>(0));
    g_ArchiveNamesAt0068BE1C.back()=new char[strlen(registeredName)+1];
    strcpy(g_ArchiveNamesAt0068BE1C.back(),registeredName);
}
}
