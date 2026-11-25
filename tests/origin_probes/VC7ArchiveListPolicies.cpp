// The archive value width is an observation, not a recovered entry declaration.
#include "VC7ListIteratorPolicies.cpp"

struct ArchiveValueObservation { unsigned char bytes[108]; };
typedef std::list<ArchiveValueObservation> ArchiveListObservation;
void ObserveArchiveList(ArchiveListObservation& entries, const ArchiveValueObservation& value) {
    if (entries.size()) {
        ArchiveListObservation::iterator current = entries.begin();
        ArchiveListObservation::iterator last = entries.end();
        if (current != last) entries.push_back(value);
    }
}
extern "C" const unsigned long ArchiveListLayout[] = {
    sizeof(ArchiveValueObservation), sizeof(ArchiveListObservation),
    sizeof(ArchiveListObservation::iterator)
};
