// Natural-C++ source alternative for the unclassified 004170B0 destructor.
// The original owner identity is unresolved; this is an ordinary pointer-owning
// class control, not an adopted game class or a complete owner-layout claim.
class ResourceInterfaceSlot8At004170B0 {
public:
    virtual void __stdcall Slot0();
    virtual void __stdcall Slot1();
    virtual void __stdcall Slot2();
};

class UnknownResourceOwnerAt004170B0 {
    ResourceInterfaceSlot8At004170B0* resource;
public:
    ~UnknownResourceOwnerAt004170B0();
};

UnknownResourceOwnerAt004170B0::~UnknownResourceOwnerAt004170B0()
{
    resource->Slot2();
}

// Probe-only delete expression: forces VC7.1 to emit the scalar-deleting
// destructor COMDAT at the companion 0041A140 shape. This helper is not a
// claim that the game contains a function with this name or source body.
void __cdecl DeleteUnknownResourceOwnerAt004170B0(
    UnknownResourceOwnerAt004170B0* owner)
{
    delete owner;
}
