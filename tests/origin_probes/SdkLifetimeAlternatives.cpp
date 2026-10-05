// Generic complete owners demonstrate outer explicit/implicit ambiguity.
// None of these classes declares a private SDK owner or target layout.
#include <new>
#include <stddef.h>

namespace D3DX {
struct png_struct_def;
struct png_info_struct;
void __cdecl png_destroy_info_struct(png_struct_def *, png_info_struct **);
}

void ProbePngDestroyInfo(D3DX::png_struct_def *state, D3DX::png_info_struct **info)
{
    D3DX::png_destroy_info_struct(state, info);
}

struct InitialState {
    int references;
    void *pointer;
    InitialState() : references(1), pointer(0) {}
};

struct ExplicitInitOwner {
    virtual void Touch() {}
    int references;
    void *pointer;
    ExplicitInitOwner() : references(1), pointer(0) {}
};

struct ImplicitInitOwner {
    virtual void Touch() {}
    InitialState state;
};

void ProbeExplicitInit(void *storage)
{
    new (storage) ExplicitInitOwner;
}

void ProbeImplicitInit(void *storage)
{
    new (storage) ImplicitInitOwner;
}

struct OwnedPointer {
    void *pointer;
    ~OwnedPointer() { ::operator delete(pointer); }
};

struct ExplicitCleanupOwner {
    void *pointer;
    ~ExplicitCleanupOwner() { ::operator delete(pointer); }
};

struct ImplicitCleanupOwner {
    OwnedPointer state;
};

void ProbeExplicitCleanup(ExplicitCleanupOwner *owner)
{
    owner->~ExplicitCleanupOwner();
}

void ProbeImplicitCleanup(ImplicitCleanupOwner *owner)
{
    owner->~ImplicitCleanupOwner();
}

struct ConditionalPointer {
    void *pointer;
    bool owned;
    ~ConditionalPointer() { if (pointer && owned) ::operator delete(pointer); }
};

struct ExplicitConditionalOwner {
    void *pointer;
    bool owned;
    ~ExplicitConditionalOwner() { if (pointer && owned) ::operator delete(pointer); }
};

struct ImplicitConditionalOwner {
    ConditionalPointer state;
};

void ProbeExplicitConditional(ExplicitConditionalOwner *owner)
{
    owner->~ExplicitConditionalOwner();
}

void ProbeImplicitConditional(ImplicitConditionalOwner *owner)
{
    owner->~ImplicitConditionalOwner();
}

extern const unsigned int LifetimeAlternativeLayout[] = {
    sizeof(void *), sizeof(InitialState), sizeof(ExplicitInitOwner), sizeof(ImplicitInitOwner),
    sizeof(ExplicitCleanupOwner), sizeof(ImplicitCleanupOwner),
    sizeof(ExplicitConditionalOwner), sizeof(ImplicitConditionalOwner)
};
