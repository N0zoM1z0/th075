#pragma once

// The record's 16-byte physical lifetime is witnessed by the native
// 60-element catalog array. One signed byte and three owned pointers
// occupy the observed offsets; alignment is natural, not fabricated.
struct MusicCatalogRecordF261 {
    signed char counter;
    char* first;
    char* second;
    char* third;
    MusicCatalogRecordF261();
    ~MusicCatalogRecordF261();
};
typedef char AssertMusicCatalogRecord16[(sizeof(MusicCatalogRecordF261)==16)?1:-1];
