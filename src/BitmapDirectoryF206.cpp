#include <windows.h>
#include <d3d8.h>
#include <stdio.h>
#include <stdlib.h>
// Private diagnostic only: record and vector owner types are deliberately
// call-only and do not establish complete original C++ class layouts.
extern const char g_BitmapFormatAt006577F4[];
class BitmapEntryF206 {
public:
    bool LoadFile(const char* path);
    void EncodeIndexedPalette();
};
class BitmapIteratorF206 {
public:
    // Original native iterator temporaries are four-byte pointer views.
    unsigned char* storage;
    BitmapIteratorF206 operator+(int offset) const;
};
typedef char IteratorPhysicalSizeF206[(sizeof(BitmapIteratorF206)==4)?1:-1];
class BitmapEntriesF206 {
public:
    int Size();
    unsigned char* At(int index);
    BitmapIteratorF206 Begin();
    BitmapIteratorF206 End();
    BitmapIteratorF206 Erase(BitmapIteratorF206 first, BitmapIteratorF206 last);
};
class BitmapHandlesF206 {
public:
    IDirect3DTexture8** At(int index);
};
namespace Graphics {
    bool Create16BitTexture(unsigned short width,unsigned short height,
                            IDirect3DTexture8** texture);
}
class TextureManagerF206 {
public:
    void LoadBitmapDirectory(const char*);
    void Refresh(int index);
};
#define ENTRIES reinterpret_cast<BitmapEntriesF206*>(reinterpret_cast<unsigned char*>(this)+8)
#define HANDLES reinterpret_cast<BitmapHandlesF206*>(reinterpret_cast<unsigned char*>(this)+0x18)
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define ENTRY(type,off) (*reinterpret_cast<type*>(ENTRIES->At(work.index)+(off)))
void TextureManagerF206::LoadBitmapDirectory(const char* baseDir)
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
        sprintf(work.filename,g_BitmapFormatAt006577F4,baseDir,work.index);
        if (reinterpret_cast<BitmapEntryF206*>(ENTRIES->At(work.index))->LoadFile(work.filename)) {
            if (ENTRY(unsigned int,4)<256 && ENTRY(unsigned int,8)<256 &&
                (ENTRY(unsigned int,8)>64 || ENTRY(unsigned int,8)>64)) {
                ENTRY(unsigned char,0x28)=1;
                reinterpret_cast<BitmapEntryF206*>(ENTRIES->At(work.index))->EncodeIndexedPalette();
            } else {
                ENTRY(unsigned char,0x28)=0;
                Graphics::Create16BitTexture(
                    ENTRY(unsigned short,4),ENTRY(unsigned short,8),HANDLES->At(work.index));
                Refresh(work.index);
                void* buffer = ENTRY(void*,0x1c);
                free(buffer);
                ENTRY(void*,0x1c) = 0;
            }
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
