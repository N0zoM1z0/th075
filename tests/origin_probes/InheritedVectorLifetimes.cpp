// Complete natural controls for inherited lifetime and ordinary cleanup policy.
#include <vector>
struct ImplicitDerivedVector : std::vector<unsigned long> {};
struct ExplicitDerivedVector : std::vector<unsigned long> {
    ExplicitDerivedVector() {}
    ~ExplicitDerivedVector() {}
};
struct ExplicitTidyDerivedVector : std::vector<unsigned long> {
    ExplicitTidyDerivedVector() {}
    ~ExplicitTidyDerivedVector() { _Tidy(); }
    void Cleanup() { _Tidy(); }
};
ImplicitDerivedVector implicit_derived;
ExplicitDerivedVector explicit_derived;
ExplicitTidyDerivedVector tidy_derived;
void OrdinaryGlobalCleanup() { tidy_derived.Cleanup(); }
extern const unsigned long inherited_vector_sizes[] = {
    sizeof(ImplicitDerivedVector), sizeof(ExplicitDerivedVector),
    sizeof(ExplicitTidyDerivedVector), sizeof(std::vector<unsigned long>)
};
