#include "DataArchive.hpp"
#include <string.h>

HANDLE DataArchiveF481::SeekNamedEntryWithSize(const char* entryName, DWORD* size)
{
    std::list<ArchiveWireEntryF250>::iterator current=entries.begin();
    std::list<ArchiveWireEntryF250>::iterator last=entries.end();
    while (current != last) {
        if (!strcmp(reinterpret_cast<const char*>(current->filename),entryName))
            break;
        current++;
    }
    if (current == last)
        return INVALID_HANDLE_VALUE;
    SetFilePointer(originalHandle,
        current->sourceOffset,0,FILE_BEGIN);
    *size = current->sourceSize;
    return originalHandle;
}
#undef originalHandle
