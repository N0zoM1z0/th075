// Generic observations; original game declarations and complete layouts are unknown.
#include <deque>
struct ClearValue8 {
    unsigned long values[2];
    ~ClearValue8();
};
struct ExplicitMember {
    std::deque<ClearValue8> values;
    ExplicitMember() { values.clear(); }
    ~ExplicitMember() { values.clear(); }
};
struct ExplicitBase : std::deque<ClearValue8> {
    ExplicitBase() { clear(); }
    ~ExplicitBase() { clear(); }
};
struct ImplicitMember {
    std::deque<ClearValue8> values;
    ImplicitMember() { values.clear(); }
};
struct ImplicitBase : std::deque<ClearValue8> {
    ImplicitBase() { clear(); }
};
template<class Owner> struct EmptyCleanup {
    ~EmptyCleanup() { static_cast<Owner*>(this)->clear(); }
};
struct EmptyFirst : EmptyCleanup<EmptyFirst>, std::deque<ClearValue8> {
    EmptyFirst() { clear(); }
};
struct EmptyAfter : std::deque<ClearValue8>, EmptyCleanup<EmptyAfter> {
    EmptyAfter() { clear(); }
};
template<class Owner> struct EmptyMemberCleanup {
    ~EmptyMemberCleanup() { static_cast<Owner*>(this)->values.clear(); }
};
struct MemberEmptyFirst : EmptyMemberCleanup<MemberEmptyFirst> {
    std::deque<ClearValue8> values;
    MemberEmptyFirst() { values.clear(); }
};
ExplicitMember explicit_member;
ExplicitBase explicit_base;
ImplicitMember implicit_member;
ImplicitBase implicit_base;
EmptyFirst empty_first;
EmptyAfter empty_after;
MemberEmptyFirst member_empty_first;
extern const unsigned long DequeOuterSizes[] = {
    sizeof(ClearValue8), sizeof(explicit_member), sizeof(explicit_base),
    sizeof(implicit_member), sizeof(implicit_base), sizeof(empty_first),
    sizeof(empty_after), sizeof(member_empty_first)
};
