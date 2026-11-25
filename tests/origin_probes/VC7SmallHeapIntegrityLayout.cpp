// Actual supplied CRT/SDK structures and independent integrity-policy controls.
// Runtime heap state and original game layouts are not declared here.
#include <stddef.h>
#include <winheap.h>

extern "C" const unsigned long SmallHeapIntegrityLayoutProbe[] = {
    sizeof(void *), sizeof(BITVEC), sizeof(HEADER),
    offsetof(HEADER, bitvEntryHi), offsetof(HEADER, bitvEntryLo),
    offsetof(HEADER, bitvCommit), offsetof(HEADER, pHeapData), offsetof(HEADER, pRegion),
    sizeof(REGION), offsetof(REGION, indGroupUse), offsetof(REGION, cntRegionSize),
    offsetof(REGION, bitvGroupHi), offsetof(REGION, bitvGroupLo), offsetof(REGION, grpHeadList),
    sizeof(GROUP), offsetof(GROUP, cntEntries), offsetof(GROUP, listHead),
    sizeof(LISTHEAD), offsetof(LISTHEAD, pEntryNext), offsetof(LISTHEAD, pEntryPrev),
    sizeof(ENTRY), offsetof(ENTRY, sizeFront), offsetof(ENTRY, pEntryNext), offsetof(ENTRY, pEntryPrev),
    sizeof(ENTRYEND), offsetof(ENTRYEND, sizeBack),
    BYTES_PER_PARA, BYTES_PER_PAGE, BYTES_PER_GROUP, BYTES_PER_REGION,
    GROUPS_PER_REGION, PAGES_PER_GROUP, ENTRY_OFFSET, OVERHEAD_PER_PAGE,
    MAX_FREE_ENTRY_SIZE, MAX_ALLOC_ENTRY_SIZE, sizeof(DWORD), sizeof(BOOL)
};

extern "C" int SmallHeapHeaderRangeControl(HEADER *headers, unsigned int count) {
    return IsBadWritePtr(headers, count * sizeof(HEADER)) == 0;
}
extern "C" int SmallHeapRegionRangeControl(REGION *region) {
    return IsBadWritePtr(region, sizeof(REGION)) == 0;
}
extern "C" int SmallHeapGroupRangeControl(void *group) {
    return IsBadWritePtr(group, BYTES_PER_GROUP) == 0;
}
extern "C" int IndependentEntryValidityControl(const ENTRY *entry) {
    int front = entry->sizeFront;
    int size = front & ~1;
    if (size < BYTES_PER_PARA || (size & (BYTES_PER_PARA - 1)) || size > MAX_FREE_ENTRY_SIZE)
        return 0;
    const ENTRYEND *back = reinterpret_cast<const ENTRYEND *>(
        reinterpret_cast<const char *>(entry) + size - sizeof(int));
    return back->sizeBack == front;
}
extern "C" int IndependentFreeListClassControl(int size) {
    int index = (size >> 4) - 1;
    return index > 63 ? 63 : index;
}
extern "C" int IndependentCommittedGroupControl(BITVEC bits) {
    return static_cast<int>(bits) >= 0;
}
