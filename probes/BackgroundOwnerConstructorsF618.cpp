// F618: native 45-byte original BackgroundStage-like polymorphic object
// constructor. The complete original source origin is UNKNOWN, not
// credited authored CODE despite actual native authored call sites.
// This ordinary explicit default ctor is the independent C++ grammar
// alternative to implicit compiler synthesis in a separate source TU.
struct BackgroundMemberAt4F618 {
    unsigned char nativeMemberStorage[0x14];
    BackgroundMemberAt4F618();
};
struct BackgroundMemberAt18F618 {
    BackgroundMemberAt18F618();
};
class BackgroundOwnerF618 {
public:
    BackgroundOwnerF618();
    virtual ~BackgroundOwnerF618();
    BackgroundMemberAt4F618 memberAt4;
    BackgroundMemberAt18F618 memberAt18;
};
BackgroundOwnerF618::BackgroundOwnerF618() {}
