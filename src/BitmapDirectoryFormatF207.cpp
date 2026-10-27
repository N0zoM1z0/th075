#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <stdlib.h>
// Physical pointer-only record/iterator interfaces for this accepted
// full-body reconstruction. Original STL element and source class
// identities remain unproved; do not instantiate external owners.
extern const char g_BitmapFormatAt00657800[];
class BitmapEntryF207 {
public:
    bool LoadFile(const char* path);
    void EncodeIndexedPalette();
};
class BitmapIteratorF207 {
public:
    // Original native iterator temporaries are four-byte pointer views.
    unsigned char* storage;
    BitmapIteratorF207 operator+(int offset) const;
};
typedef char IteratorPhysicalSizeF207[(sizeof(BitmapIteratorF207)==4)?1:-1];
class BitmapEntriesF207 {
public:
    int Size();
    unsigned char* At(int index);
    BitmapIteratorF207 Begin();
    BitmapIteratorF207 End();
    BitmapIteratorF207 Erase(BitmapIteratorF207 first, BitmapIteratorF207 last);
};
class BitmapHandlesF207 {
public:
    IDirect3DTexture8** At(int index);
};
namespace Graphics {
    bool CreateTexture(unsigned short width, unsigned short height,
                       IDirect3DTexture8** texture, unsigned char bitsPerPixel);
}
class TextureManagerF207 {
public:
    void LoadBitmapDirectoryWithFormat(const char*);
    void Refresh(int index);
};
#define ENTRIES reinterpret_cast<BitmapEntriesF207*>(reinterpret_cast<unsigned char*>(this)+8)
#define HANDLES reinterpret_cast<BitmapHandlesF207*>(reinterpret_cast<unsigned char*>(this)+0x18)
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define ENTRY(type,off) (*reinterpret_cast<type*>(ENTRIES->At(work.index)+(off)))
void TextureManagerF207::LoadBitmapDirectoryWithFormat(const char* baseDir)
{
    struct BitmapDirectoryWork {
    int index;
    int total;
    char filename[260];
    } work;
    work.total = ENTRIES->Size();
    for (work.index=0; work.index<work.total; ++work.index) {
        ENTRY(unsigned char,0) = FIELD(unsigned char,0x4c);
        ENTRY(DWORD,0x14) = FIELD(DWORD,4);
        sprintf(work.filename,g_BitmapFormatAt00657800,baseDir,work.index);
        if (reinterpret_cast<BitmapEntryF207*>(ENTRIES->At(work.index))->LoadFile(work.filename)) {
            ENTRY(unsigned char,0x28)=0;
            Graphics::CreateTexture(ENTRY(unsigned short,4),
                ENTRY(unsigned short,8),HANDLES->At(work.index),ENTRY(unsigned char,0));
            Refresh(work.index);
            void* buffer = ENTRY(void*,0x1c);
            free(buffer);
            ENTRY(void*,0x1c) = 0;
        } else {
            ENTRIES->Erase(ENTRIES->Begin() + work.index, ENTRIES->End());
            work.total = work.index;
        }
    }
}
#undef ENTRY
#undef FIELD
#undef HANDLES
#undef ENTRIES
