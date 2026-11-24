#pragma once

#include <deque>

class DataArchiveF481;

typedef std::deque<DataArchiveF481*> ArchiveObjects;
typedef std::deque<char*> ArchiveNames;

extern ArchiveObjects g_ArchiveObjectsAt0068BE08;
extern ArchiveNames g_ArchiveNamesAt0068BE1C;
extern unsigned int g_ArchiveUseCountAt0068BE04;

namespace ResourceLookupF217
{
    DataArchiveF481* FindByName(const char* name);
}
