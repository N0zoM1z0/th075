// F687: full original optimized COM/resource owner destructor C++ grammar.
// Complete native 00608D8E (58B) and 00608F96 (64B) both match their
// original PE after only the genuine vtable/call/IAT COFF fields link.
// Historical SDK class/author identities are UNKNOWN. The native virtual
// method slots are observed byte offsets: 8 and 0xE0. No fabricated
// 57-function interface class, dummy member padding or inline ASM.
extern "C" __declspec(dllimport) void __stdcall ImportedFree(void*);
class SDKResourceF687 { public: void Reset(); void Destroy(); };
class SDKResourceOwnerF687 { public: virtual ~SDKResourceOwnerF687(); };
class SDKCOMOwnerF687 { public: virtual ~SDKCOMOwnerF687(); };
typedef void (__stdcall *NativeCOMReleaseF687)(void*);
typedef void (__stdcall *NativeCOMHandleF687)(void*,void*);
#define OBJ_PTR(off,type) (*reinterpret_cast<type**>(reinterpret_cast<char*>(this)+(off)))
SDKResourceOwnerF687::~SDKResourceOwnerF687() {
    if (OBJ_PTR(0x48,SDKResourceF687)) {
        OBJ_PTR(0x48,SDKResourceF687)->Reset();
        OBJ_PTR(0x48,SDKResourceF687)->Destroy();
    }
    if (OBJ_PTR(8,void)) ImportedFree(OBJ_PTR(8,void));
    if (OBJ_PTR(0x4c,void))
        (reinterpret_cast<NativeCOMReleaseF687*>(*reinterpret_cast<void***>(OBJ_PTR(0x4c,void))))[2](OBJ_PTR(0x4c,void));
}
SDKCOMOwnerF687::~SDKCOMOwnerF687() {
    if (OBJ_PTR(8,void)) {
        if (OBJ_PTR(0x14,void))
            (reinterpret_cast<NativeCOMHandleF687*>(*reinterpret_cast<void***>(OBJ_PTR(8,void))))[0xE0/4](OBJ_PTR(8,void),OBJ_PTR(0x14,void));
        if (OBJ_PTR(0x10,void))
            (reinterpret_cast<NativeCOMHandleF687*>(*reinterpret_cast<void***>(OBJ_PTR(8,void))))[0xE0/4](OBJ_PTR(8,void),OBJ_PTR(0x10,void));
        (reinterpret_cast<NativeCOMReleaseF687*>(*reinterpret_cast<void***>(OBJ_PTR(8,void))))[2](OBJ_PTR(8,void));
    }
}
#undef OBJ_PTR
