// F787 research: complete natural VC7.1 implicit assignment source of
// the original 0045AAE0. Origin is STILL UNKNOWN (do not credit authored
// bytes); the 116B borrowed layout is physically constrained by the PE.
#include <new>
#include <stddef.h>
// Physical 116B composite, not the original owner/name. Native fields
// observed on the original PE, nested 16B vector-like values +0x54/+0x64.
class NestedSequenceF787 {
public:
    unsigned char physical16[16];
    NestedSequenceF787();
    NestedSequenceF787(const NestedSequenceF787&);
    ~NestedSequenceF787();
    NestedSequenceF787& operator=(const NestedSequenceF787&);
};
// Two physical 16-byte POD blocks, not arbitrary padding.
struct NativeCopyHeaderF787 {
    unsigned int dword00,dword04,dword08,dword0c;
};
struct NativeCopyTailF787 { unsigned int w0,w4,w8,wc; };
// Remaining distinct short/int fields and two observed nested 16B owners.
struct CompositeValueF787 {
    NativeCopyHeaderF787 header;
    unsigned short short10;
    unsigned int dword14;
    unsigned short short18,short1a,short1c,short1e,short20,short22,short24,short26,short28,short2a;
    unsigned int dword2c,dword30;
    unsigned short short34,short36;
    unsigned char byte38;
    unsigned int dword3c,dword40;
    NativeCopyTailF787 tail44;
    NestedSequenceF787 first, second;
};
typedef char VerifySizeF787[(sizeof(CompositeValueF787)==116)?1:-1];
typedef char VerifyTailF787[(offsetof(CompositeValueF787,tail44)==0x44)?1:-1];
typedef char VerifyFirstF787[(offsetof(CompositeValueF787,first)==0x54)?1:-1];
typedef char VerifySecondF787[(offsetof(CompositeValueF787,second)==0x64)?1:-1];
void ProbeCompositeCopyF787(CompositeValueF787* dest,
                            const CompositeValueF787* source) {
    new(dest) CompositeValueF787(*source);
}
void ProbeCompositeAssignmentF787(CompositeValueF787* dest,
                            const CompositeValueF787* source) {
    *dest=*source;
}
