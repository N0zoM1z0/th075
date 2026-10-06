// Complete generic controls; widths do not identify original game declarations.
#include <vector>
struct SixteenByteObservation { unsigned char bytes[16]; };
struct OneHundredSixteenByteObservation { unsigned char bytes[116]; };
std::vector<SixteenByteObservation> observed_sixteen;
std::vector<OneHundredSixteenByteObservation> observed_large;
std::vector<unsigned long> observed_words;
extern void ObserveNeighborPolicy();
struct SixteenVectorPolicy : std::vector<SixteenByteObservation> {
    SixteenVectorPolicy() { Cleanup(); }
    ~SixteenVectorPolicy() { ObserveNeighborPolicy(); }
    void Cleanup() { _Tidy(); }
};
struct LargeVectorPolicy : std::vector<OneHundredSixteenByteObservation> {
    unsigned short first, second;
    LargeVectorPolicy() { Cleanup(); first = 0; second = 0; }
    ~LargeVectorPolicy() { ObserveNeighborPolicy(); }
    void Cleanup() { _Tidy(); }
};
struct WordVectorPolicy : std::vector<unsigned long> {
    WordVectorPolicy() { ObserveNeighborPolicy(); }
    ~WordVectorPolicy() { ObserveNeighborPolicy(); }
    void Cleanup() { _Tidy(); }
};
SixteenVectorPolicy observed_sixteen_policy;
LargeVectorPolicy observed_large_policy;
WordVectorPolicy observed_word_policy;
void ClearSixteenPolicy() { observed_sixteen_policy.Cleanup(); }
void ClearLargePolicy() { observed_large_policy.Cleanup(); }
void ClearWordPolicy() { observed_word_policy.Cleanup(); }
struct ThreeVectorObservation {
    std::vector<SixteenByteObservation> first, second;
    std::vector<OneHundredSixteenByteObservation> large;
    ThreeVectorObservation() { ObserveNeighborPolicy(); }
    ~ThreeVectorObservation() { ObserveNeighborPolicy(); }
};
ThreeVectorObservation observed_three_vectors;
extern const unsigned long neighbor_vector_sizes[] = {
    sizeof(SixteenByteObservation), sizeof(OneHundredSixteenByteObservation),
    sizeof(unsigned long), sizeof(SixteenVectorPolicy), sizeof(LargeVectorPolicy),
    sizeof(WordVectorPolicy), sizeof(ThreeVectorObservation)
};
