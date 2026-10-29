// F618 independent C++ implicit default ctor alternative: NO declared
// constructor for the owning original polymorphic type. Natural
// placement-new forces VC7.1 to emit the real 45-byte code grammar.
// Source provenance remains UNKNOWN even after full linked PE bytes.
struct BackgroundMemberAt4F618 {
    unsigned char nativeMemberStorage[0x14];
    BackgroundMemberAt4F618();
};
struct BackgroundMemberAt18F618 {
    BackgroundMemberAt18F618();
};
class BackgroundOwnerF618 {
public:
    virtual ~BackgroundOwnerF618();
    BackgroundMemberAt4F618 memberAt4;
    BackgroundMemberAt18F618 memberAt18;
};
#include <new>
void __cdecl F618ForceNativeImplicitCtor(BackgroundOwnerF618* object) {
    new (object) BackgroundOwnerF618;
}
