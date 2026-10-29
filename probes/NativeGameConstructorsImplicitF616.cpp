// F616 independent implicit default-special-member alternative.
// Ordinary VC7.1 C++ syntax and placement-new force natural compiler
// generation of the THREE ORIGINAL CODE-shaped constructors. The native
// original developer-written-vs-generated provenance is still UNKNOWN.
// F616: reconstruct complete game-specific native constructor shapes.
// Original source origin for these three whole native functions is
// UNKNOWN: ordinary VC7.1 implicit/explicit constructor ownership is
// ambiguous, so no authored exact CODE or historical class names claimed.
// Real observed vtable/member offsets are derived from the original PE.
class GameMemberF616 {
public:
    GameMemberF616();
};

class SceneBaseWithMemberF616 {
public:
    virtual ~SceneBaseWithMemberF616();
    GameMemberF616 gameMemberAt4;
};


class AuxiliaryBaseF616 {
public:
    virtual ~AuxiliaryBaseF616();
};


class AuxiliaryDerivedF616 : public AuxiliaryBaseF616 {
public:
    virtual ~AuxiliaryDerivedF616();
};


// Construct real objects through normal placement-new to force their
// genuinely implicit VC7.1 default special-member generation.
#include <new>
void __cdecl F616ForceImplicit(SceneBaseWithMemberF616* scene,
                               AuxiliaryBaseF616* base,
                               AuxiliaryDerivedF616* derived) {
    new (scene) SceneBaseWithMemberF616;
    new (base) AuxiliaryBaseF616;
    new (derived) AuxiliaryDerivedF616;
}
