#include "DataArchive.hpp"
#include <string.h>

HANDLE DataArchiveF481::SeekNamedEntry(const char* name)
{
    std::list<ArchiveWireEntryF250>::iterator current=entries.begin();
    std::list<ArchiveWireEntryF250>::iterator last=entries.end();
    while (current != last) {
        if (!strcmp(reinterpret_cast<const char*>(current->filename),name)) break;
        current++;
    }
    if (current == last) return INVALID_HANDLE_VALUE;
    SetFilePointer(originalHandle, current->sourceOffset, 0, FILE_BEGIN);
    return originalHandle;
}
