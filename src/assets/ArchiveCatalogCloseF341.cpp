#include "assets/ArchiveCatalog.hpp"
#include "assets/DataArchive.hpp"
#include <string.h>

void ArchiveCatalog::CloseNamed(const char* name)
{
    ArchiveNames::iterator nameIt = g_ArchiveNamesAt0068BE1C.begin();
    ArchiveNames::iterator nameLimit = g_ArchiveNamesAt0068BE1C.end();
    ArchiveObjects::iterator archiveEntry = g_ArchiveObjectsAt0068BE08.begin();
    ArchiveObjects::iterator resourceEnd = g_ArchiveObjectsAt0068BE08.end();
    while (nameIt != nameLimit) {
        if (!strcmp(*nameIt, name)) {
            delete *archiveEntry;
            archiveEntry = g_ArchiveObjectsAt0068BE08.erase(archiveEntry);
            nameIt = g_ArchiveNamesAt0068BE1C.erase(nameIt);
        } else {
            nameIt++;
            archiveEntry++;
        }
    }
}
