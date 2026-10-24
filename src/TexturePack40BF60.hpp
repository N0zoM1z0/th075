#pragma once
#include "SpriteDraw40CA80.hpp"
#include <stdio.h>

// Pointer-only views; complete original owner and bitmap layouts are unknown.
class BitmapPalette40C380 { public: void Load(const char*); };
class TextureEntryCount40C8C0 { public: unsigned int Size(); };
class BitmapPackSource40BF60 { public: bool LoadFile(const char*); void Encode(); };
class TexturePack40BF60 {
public:
    void Save(const char*, const char*, signed char);
    void SaveDefault(const char*, const char*);
};

// Complete source-compatible serialization value; original grouping is unknown.
struct TextureRecordSnapshot40BF60 {
    int width, height, stride;
    unsigned char depth;
    DWORD encodedSize;
    void* data;
};
typedef char RecordSize40BF60[(sizeof(TextureRecordSnapshot40BF60) == 24) ? 1 : -1];
typedef char RecordDepth40BF60[(offsetof(TextureRecordSnapshot40BF60, depth) == 12) ? 1 : -1];
typedef char RecordEncoded40BF60[(offsetof(TextureRecordSnapshot40BF60, encodedSize) == 16) ? 1 : -1];
typedef char RecordData40BF60[(offsetof(TextureRecordSnapshot40BF60, data) == 20) ? 1 : -1];

typedef char RecordWidth40BF60[(offsetof(TextureRecordSnapshot40BF60, width) == 0) ? 1 : -1];
typedef char RecordHeight40BF60[(offsetof(TextureRecordSnapshot40BF60, height) == 4) ? 1 : -1];
typedef char RecordStride40BF60[(offsetof(TextureRecordSnapshot40BF60, stride) == 8) ? 1 : -1];
