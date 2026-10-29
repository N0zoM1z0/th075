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
    SceneBaseWithMemberF616();
    virtual ~SceneBaseWithMemberF616();
    GameMemberF616 gameMemberAt4;
};

SceneBaseWithMemberF616::SceneBaseWithMemberF616() {}

class AuxiliaryBaseF616 {
public:
    AuxiliaryBaseF616();
    virtual ~AuxiliaryBaseF616();
};

AuxiliaryBaseF616::AuxiliaryBaseF616() {}

class AuxiliaryDerivedF616 : public AuxiliaryBaseF616 {
public:
    AuxiliaryDerivedF616();
    virtual ~AuxiliaryDerivedF616();
};

AuxiliaryDerivedF616::AuxiliaryDerivedF616() {}
