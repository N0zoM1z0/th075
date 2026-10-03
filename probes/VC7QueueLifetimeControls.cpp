// Synthetic lifetime controls, not recovered complete game owner layouts.
#include <new>
struct QueueServiceProbe {
    QueueServiceProbe(int interval = 16);
    ~QueueServiceProbe();
};
struct ExplicitConstructProbe {
    ExplicitConstructProbe();
};
ExplicitConstructProbe::ExplicitConstructProbe() {
    QueueServiceProbe local;
}
struct ExplicitDestroyProbe {
    ~ExplicitDestroyProbe();
};
ExplicitDestroyProbe::~ExplicitDestroyProbe() {
    QueueServiceProbe local;
}
struct ImplicitConstructProbe {
    QueueServiceProbe member;
};
ImplicitConstructProbe* MakeImplicitConstruct(ImplicitConstructProbe* storage) {
    return new (storage) ImplicitConstructProbe;
}

void DestroyImplicit(ImplicitConstructProbe* value) { value->~ImplicitConstructProbe(); }
struct ExplicitPersistentProbe { QueueServiceProbe member; ExplicitPersistentProbe(); ~ExplicitPersistentProbe(); };
ExplicitPersistentProbe::ExplicitPersistentProbe() {}
ExplicitPersistentProbe::~ExplicitPersistentProbe() {}
void ExplicitPulseProbe() { QueueServiceProbe local; }
struct EmptyInitValue {};
EmptyInitValue generated_global_probe = (QueueServiceProbe(), EmptyInitValue());
extern EmptyInitValue existing_empty_probe;
EmptyInitValue generated_copy_probe = (QueueServiceProbe(), existing_empty_probe);
struct MemberPulseProbe { MemberPulseProbe* Pulse(); };
MemberPulseProbe* MemberPulseProbe::Pulse() { QueueServiceProbe local; return this; }
