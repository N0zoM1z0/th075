// F691: whole original 249-byte COM-manager cleanup source grammar.
// Real original COM callback ABI slots +8/+E0, member offsets and linked list.
// All 104 original x86 and five genuine original PE/COFF fields are exact
// after linking; class names/types remain provisional original source owner.
extern "C" __declspec(dllimport) void __stdcall ImportedFree(void*);
extern "C" __declspec(dllimport) void __stdcall ImportedDispose(void*);
extern "C" __declspec(dllimport) void __stdcall ImportedReleasePair(void*,void*);
typedef void (__stdcall *NativeCOMRelease)(void*);
typedef void (__stdcall *NativeCOMHandle)(void*,void*);
class SDKCOMManagerF691 {public: void Clear();};
extern SDKCOMManagerF691* g_SDKCOMManagerHeadF691;
#define OBJ_PTR(off) (*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+(off)))
#define TABLE(obj) (*reinterpret_cast<void***>(obj))
#define VIRTUAL_RELEASE(obj) reinterpret_cast<NativeCOMRelease*>(TABLE(obj))[2](obj)
#define VIRTUAL_HANDLE(obj,handle) reinterpret_cast<NativeCOMHandle*>(TABLE(obj))[0xE0/4](obj,handle)
void SDKCOMManagerF691::Clear() {
    if (OBJ_PTR(0x64)) VIRTUAL_HANDLE(OBJ_PTR(4),OBJ_PTR(0x64));
    if (OBJ_PTR(0x68)) VIRTUAL_HANDLE(OBJ_PTR(4),OBJ_PTR(0x68));
    for (int i=0;i<8;++i) {
        void* first = OBJ_PTR(0x30+4*i);
        if (first) { VIRTUAL_RELEASE(first); OBJ_PTR(0x30+4*i)=0; }
        void* second = OBJ_PTR(0x10+4*i);
        if (second) { VIRTUAL_RELEASE(second); OBJ_PTR(0x10+4*i)=0; }
    }
    void* ptr = OBJ_PTR(0x0C);
    if (ptr) { VIRTUAL_RELEASE(ptr); OBJ_PTR(0x0C)=0; }
    ptr = OBJ_PTR(4);
    if (ptr) { VIRTUAL_RELEASE(ptr); OBJ_PTR(4)=0; }
    if (OBJ_PTR(0x6C)&&OBJ_PTR(0xA8)) ImportedReleasePair(OBJ_PTR(0x6C),OBJ_PTR(0xA8));
    if (OBJ_PTR(0x6C)&&OBJ_PTR(0x9C)) ImportedReleasePair(OBJ_PTR(0x6C),OBJ_PTR(0x9C));
    if (OBJ_PTR(0x98)) ImportedFree(OBJ_PTR(0x98));
    if (OBJ_PTR(0x6C)) ImportedDispose(OBJ_PTR(0x6C));
    SDKCOMManagerF691** cursor = &g_SDKCOMManagerHeadF691;
    while (*cursor && *cursor != this)
        cursor=reinterpret_cast<SDKCOMManagerF691**>(reinterpret_cast<char*>(*cursor)+0xAC);
    if (*cursor) *cursor=*reinterpret_cast<SDKCOMManagerF691**>(reinterpret_cast<char*>(*cursor)+0xAC);
}
#undef OBJ_PTR
#undef TABLE
#undef VIRTUAL_RELEASE
#undef VIRTUAL_HANDLE
