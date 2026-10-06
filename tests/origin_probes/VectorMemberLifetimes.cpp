// Complete observations for vendor members and ordinary inherited policies.
#include <vector>
struct FortyFourByteObservation { unsigned char bytes[44]; };
std::vector<unsigned long> observed_words;
std::vector<FortyFourByteObservation> observed_records;
void ClearObservedWords() { observed_words.clear(); }
void ClearObservedRecords() { observed_records.clear(); }
extern void ObserveVectorPolicy();
struct WordVectorPolicy : std::vector<unsigned long> {
    WordVectorPolicy() { ObserveVectorPolicy(); }
    ~WordVectorPolicy() { ObserveVectorPolicy(); }
    void Cleanup() { _Tidy(); }
};
struct RecordVectorPolicy : std::vector<FortyFourByteObservation> {
    RecordVectorPolicy() { ObserveVectorPolicy(); }
    ~RecordVectorPolicy() { ObserveVectorPolicy(); }
    void Cleanup() { _Tidy(); }
};
WordVectorPolicy observed_word_policy;
RecordVectorPolicy observed_record_policy;
void ClearWordPolicy() { observed_word_policy.Cleanup(); }
void ClearRecordPolicy() { observed_record_policy.Cleanup(); }
struct ThreeVectorObservation {
    std::vector<FortyFourByteObservation> records;
    std::vector<unsigned long> first_words;
    std::vector<unsigned long> second_words;
    ThreeVectorObservation() { ObserveVectorPolicy(); }
    ~ThreeVectorObservation() { ObserveVectorPolicy(); }
};
ThreeVectorObservation observed_three_vectors;
extern const unsigned long member_vector_sizes[] = {
    sizeof(FortyFourByteObservation), sizeof(unsigned long),
    sizeof(WordVectorPolicy), sizeof(RecordVectorPolicy),
    sizeof(ThreeVectorObservation)
};
