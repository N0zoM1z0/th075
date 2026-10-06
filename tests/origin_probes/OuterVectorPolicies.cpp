// Generic observations; no original game declaration or layout is asserted.
#include <vector>
struct Value16 { unsigned char bytes[16]; };
struct Value116 { unsigned char bytes[116]; };
template<class Value> struct ExplicitPolicy : std::vector<Value> {
    ExplicitPolicy() { Cleanup(); }
    ~ExplicitPolicy() { Cleanup(); }
    void Cleanup() { this->_Tidy(); }
};
template<class Value> struct ExplicitShortPolicy : std::vector<Value> {
    unsigned short first, second;
    ExplicitShortPolicy() { Cleanup(); first = 0; second = 0; }
    ~ExplicitShortPolicy() { Cleanup(); }
    void Cleanup() { this->_Tidy(); }
};
template<class Owner> struct EmptyCleanup {
    ~EmptyCleanup() { static_cast<Owner*>(this)->_Tidy(); }
};
struct Implicit16 : std::vector<Value16>, EmptyCleanup<Implicit16> {
    using std::vector<Value16>::_Tidy;
    Implicit16() { Cleanup(); }
    void Cleanup() { _Tidy(); }
};
struct Implicit116 : std::vector<Value116>, EmptyCleanup<Implicit116> {
    using std::vector<Value116>::_Tidy;
    unsigned short first, second;
    Implicit116() { Cleanup(); first = 0; second = 0; }
    void Cleanup() { _Tidy(); }
};
struct EmptyFirst16 : EmptyCleanup<EmptyFirst16>, std::vector<Value16> {
    using std::vector<Value16>::_Tidy;
    EmptyFirst16() { Cleanup(); }
    void Cleanup() { _Tidy(); }
};
struct EmptyFirst116 : EmptyCleanup<EmptyFirst116>, std::vector<Value116> {
    using std::vector<Value116>::_Tidy;
    unsigned short first, second;
    EmptyFirst116() { Cleanup(); first = 0; second = 0; }
    void Cleanup() { _Tidy(); }
};
template<class Value> struct ImplicitSingle : std::vector<Value> {
    ImplicitSingle() { Cleanup(); }
    void Cleanup() { this->_Tidy(); }
};
template<class Value> struct ImplicitShort : std::vector<Value> {
    unsigned short first, second;
    ImplicitShort() { Cleanup(); first = 0; second = 0; }
    void Cleanup() { this->_Tidy(); }
};
template<class Value> struct PublicVectorMember : std::vector<Value> {
    void Cleanup() { this->_Tidy(); }
};
struct ImplicitMember16 {
    PublicVectorMember<Value16> values;
    ImplicitMember16() { values.Cleanup(); }
};
struct ImplicitMember116 {
    PublicVectorMember<Value116> values;
    unsigned short first, second;
    ImplicitMember116() { values.Cleanup(); first = 0; second = 0; }
};
ImplicitSingle<Value16> single16;
ImplicitShort<Value116> single116;
ImplicitMember16 member16;
ImplicitMember116 member116;
void DeleteExplicit16(ExplicitPolicy<Value16>* value) { delete value; }
void DeleteExplicit116(ExplicitShortPolicy<Value116>* value) { delete value; }
ExplicitPolicy<Value16> explicit16;
ExplicitShortPolicy<Value116> explicit116;
Implicit16 implicit16;
Implicit116 implicit116;
EmptyFirst16 empty_first16;
EmptyFirst116 empty_first116;
extern const unsigned long OuterPolicySizes[] = {
    sizeof(explicit16), sizeof(explicit116), sizeof(implicit16),
    sizeof(implicit116), sizeof(empty_first16), sizeof(EmptyCleanup<Implicit16>),
    sizeof(single16), sizeof(single116), sizeof(member16), sizeof(member116),
    sizeof(empty_first116)
};
