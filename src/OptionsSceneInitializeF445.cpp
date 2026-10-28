// Independently complete original R109 251-byte derived options scene
// constructor. Pinned VC7.1 /GX emits original vtable, new(0x50),
// four resource calls and original compiler-managed EH without grafts.
// Borrowed native 8-byte scene base, 80-byte texture object and true options
// texture surface destination. Complete original R109 scene ctor candidate.
#include <windows.h>
#include <d3d8.h>
class OptionsBaseF445 {
    void* configuration;
public: OptionsBaseF445();virtual ~OptionsBaseF445();
};
class OptionsTextureF445 {
    unsigned char observedStorage[80];
public:OptionsTextureF445();void AllocateSlots(int);void LoadArchive(const char*,const char*);
};
typedef char VerifyOptionsTexture80F445[(sizeof(OptionsTextureF445)==80)?1:-1];
extern const char g_OptionsDataPathAt00657D80[];
extern const char g_OptionsArchiveRootAt00657D78[];
extern void __cdecl OptionsCreateSurfaceAt00401C20(int width,int height,IDirect3DTexture8** output,int format);
class OptionsSceneInitF445 : public OptionsBaseF445 {
    OptionsTextureF445* texture;
    IDirect3DTexture8* canvas;
    unsigned short currentItem;
    unsigned short pressedItem;
    unsigned char mode;
public:
    OptionsSceneInitF445();virtual ~OptionsSceneInitF445();
    void InitializeOptionIndex(unsigned char item);
};
OptionsSceneInitF445::OptionsSceneInitF445() {
    canvas=0;
    texture=new OptionsTextureF445;
    texture->AllocateSlots(3);
    texture->LoadArchive(g_OptionsDataPathAt00657D80,g_OptionsArchiveRootAt00657D78);
    OptionsCreateSurfaceAt00401C20(0x400,0x200,&canvas,0x20);
    mode=5;
    currentItem=0;
    pressedItem=0;
    InitializeOptionIndex(static_cast<unsigned char>(currentItem));
}
