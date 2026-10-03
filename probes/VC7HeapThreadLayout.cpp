// Natural private CRT layout controls; these are not game owner declarations.
#include <stddef.h>
#include <winheap.h>
#include <mtdll.h>

extern "C" const unsigned long HeapThreadLayoutProbe[] = {
    sizeof(HEADER), offsetof(HEADER, bitvEntryHi), offsetof(HEADER, bitvEntryLo),
    offsetof(HEADER, bitvCommit), offsetof(HEADER, pHeapData), offsetof(HEADER, pRegion),
    sizeof(REGION), offsetof(REGION, indGroupUse), offsetof(REGION, cntRegionSize),
    offsetof(REGION, bitvGroupHi), offsetof(REGION, bitvGroupLo), offsetof(REGION, grpHeadList),
    sizeof(GROUP), offsetof(GROUP, cntEntries), offsetof(GROUP, listHead),
    sizeof(LISTHEAD), offsetof(LISTHEAD, pEntryNext), offsetof(LISTHEAD, pEntryPrev),
    sizeof(ENTRY), offsetof(ENTRY, sizeFront), offsetof(ENTRY, pEntryNext), offsetof(ENTRY, pEntryPrev),
    sizeof(ENTRYEND), offsetof(ENTRYEND, sizeBack),
    BYTES_PER_PARA, BYTES_PER_PAGE, BYTES_PER_GROUP, BYTES_PER_REGION,
    ENTRY_OFFSET, MAX_FREE_ENTRY_SIZE, HEAP_ZERO_MEMORY, MEM_RESERVE, MEM_COMMIT,
    MEM_DECOMMIT, MEM_RELEASE, PAGE_READWRITE,
    sizeof(_tiddata), offsetof(_tiddata, _tid), offsetof(_tiddata, _thandle),
    offsetof(_tiddata, _terrno), offsetof(_tiddata, _holdrand), offsetof(_tiddata, _pxcptacttab)
};
