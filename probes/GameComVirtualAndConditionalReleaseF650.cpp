// F650: natural VC7.1 whole original game-facing object methods.
// Complete source provenance and original class names are UNKNOWN.
// The actual code requires an ordinary stdcall third virtual dispatch
// and a genuine conditional CRT free of an actually owned member.
extern "C" void __cdecl free(void*);

struct VirtualStdcallInterfaceF650 {
    virtual void __stdcall First() = 0;
    virtual void __stdcall Second() = 0;
    virtual void __stdcall Third() = 0;
};
class VirtualDispatchOwnerF650 {
public:
    VirtualStdcallInterfaceF650* receiver;
    void Dispatch();
};
void VirtualDispatchOwnerF650::Dispatch() {
    receiver->Third();
}

class ConditionalReleaseOwnerF650 {
public:
    void Release();
};
void ConditionalReleaseOwnerF650::Release() {
    if (*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+8)) {
        void* pointer=*reinterpret_cast<void**>(reinterpret_cast<char*>(this)+8);
        free(pointer);
    }
}
