#include "assets/ArchiveCatalog.hpp"
#include <string.h>

ArchiveObjects g_ArchiveObjectsAt0068BE08;
ArchiveNames g_ArchiveNamesAt0068BE1C;
unsigned int g_ArchiveUseCountAt0068BE04;

namespace ResourceLookupF217 {
DataArchiveF481* FindByName(const char* name)
{
    unsigned int index;
    for (index=0; index < g_ArchiveNamesAt0068BE1C.size(); ++index) {
        if (!strcmp(g_ArchiveNamesAt0068BE1C.at(index), name))
            break;
    }
    if (index >= g_ArchiveNamesAt0068BE1C.size())
        return 0;
    return g_ArchiveObjectsAt0068BE08.at(index);
}
}
