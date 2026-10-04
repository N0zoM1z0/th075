// Complete small owners observe operations; original game layouts are unrecovered.
#include <deque>
#include <vector>
#include <new>
struct LifetimeValueObservation { unsigned long value; };
typedef std::deque<LifetimeValueObservation> LifetimeDeque;
struct LifetimeTextureObservation {
    LifetimeTextureObservation();
    ~LifetimeTextureObservation();
};
typedef std::vector<LifetimeValueObservation*> LifetimePointerVector;
struct ExplicitLifetimeConstruction {
    LifetimeDeque queues[2];
    LifetimeTextureObservation textures;
    LifetimePointerVector pointers;
    ExplicitLifetimeConstruction() {
        queues[0].clear();
        queues[1].clear();
        pointers.clear();
    }
};
struct ImplicitLifetimeConstruction {
    LifetimeDeque queues[2];
    LifetimeTextureObservation textures;
    LifetimePointerVector pointers;
};
void ObserveExplicitLifetimeConstruction(ExplicitLifetimeConstruction* p) { new (p) ExplicitLifetimeConstruction; }
void ObserveImplicitLifetimeConstruction(ImplicitLifetimeConstruction* p) { new (p) ImplicitLifetimeConstruction; }
extern "C" __declspec(dllimport) void* __stdcall SelectLifetimeObject(void*, void*);
extern "C" __declspec(dllimport) int __stdcall DeleteLifetimeObject(void*);
extern "C" __declspec(dllimport) int __stdcall ReleaseLifetimeDC(void*, void*);
struct ExplicitLifetimeRaster {
    void* window;
    void* dc;
    unsigned width;
    void* previous_object;
    unsigned char* storage;
    ~ExplicitLifetimeRaster() {
        if (storage) { delete storage; storage = 0; }
        DeleteLifetimeObject(SelectLifetimeObject(dc, previous_object));
        ReleaseLifetimeDC(window, dc);
        width = 0;
        previous_object = 0;
        dc = 0;
    }
};
struct ImplicitLifetimeRaster {
    void* window;
    void* dc;
    unsigned width;
    void* previous_object;
    unsigned char* storage;
};
void ObserveExplicitLifetimeRaster(ExplicitLifetimeRaster* p) { p->~ExplicitLifetimeRaster(); }
void ObserveImplicitLifetimeRaster(ImplicitLifetimeRaster* p) { p->~ImplicitLifetimeRaster(); }
struct LifetimeInterfaceObservation {
    virtual long __stdcall query(const void*, void**) = 0;
    virtual unsigned long __stdcall add_reference() = 0;
    virtual unsigned long __stdcall release() = 0;
};
struct ExplicitLifetimeInterface {
    LifetimeInterfaceObservation* resource;
    ~ExplicitLifetimeInterface() { resource->release(); }
};
struct OrdinaryLifetimeSmartOwner {
    LifetimeInterfaceObservation* resource;
    ~OrdinaryLifetimeSmartOwner() { resource->release(); }
};
struct ImplicitLifetimeInterface { OrdinaryLifetimeSmartOwner resource; };
void ObserveExplicitLifetimeInterface(ExplicitLifetimeInterface* p) { p->~ExplicitLifetimeInterface(); }
void ObserveImplicitLifetimeInterface(ImplicitLifetimeInterface* p) { p->~ImplicitLifetimeInterface(); }
extern "C" const unsigned long RemainingLifetimeLayout[] = {
    sizeof(LifetimeDeque), sizeof(LifetimeTextureObservation), sizeof(LifetimePointerVector),
    sizeof(ExplicitLifetimeConstruction), sizeof(ImplicitLifetimeConstruction),
    sizeof(ExplicitLifetimeRaster), sizeof(ImplicitLifetimeRaster),
    sizeof(LifetimeInterfaceObservation*), sizeof(LifetimeInterfaceObservation),
    sizeof(ExplicitLifetimeInterface), sizeof(OrdinaryLifetimeSmartOwner),
    sizeof(ImplicitLifetimeInterface)
};
