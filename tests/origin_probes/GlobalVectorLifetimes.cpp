// Complete ordinary source observations, not original game declarations.
#include <vector>
struct EightyByteValue { unsigned char bytes[80]; };
std::vector<unsigned long> direct_words;
std::vector<EightyByteValue> direct_records;
struct ImplicitVectorOwner { std::vector<unsigned long> values; };
struct ExplicitVectorOwner {
    std::vector<unsigned long> values;
    ExplicitVectorOwner() {}
    ~ExplicitVectorOwner() {}
};
ImplicitVectorOwner implicit_words;
ExplicitVectorOwner explicit_words;
void ClearDirectWords() { direct_words.clear(); }
void ClearDirectRecords() { direct_records.clear(); }
void ClearImplicitWords() { implicit_words.values.clear(); }
void ClearExplicitWords() { explicit_words.values.clear(); }
extern const unsigned long vector_lifetime_sizes[] = {
    sizeof(unsigned long), sizeof(EightyByteValue),
    sizeof(std::vector<unsigned long>), sizeof(std::vector<EightyByteValue>),
    sizeof(ImplicitVectorOwner), sizeof(ExplicitVectorOwner)
};
