// Complete generic record observation; no original character entry is recovered.
#include "VC7CharacterListPolicies.cpp"
CharacterValueObservation& ObserveCharacterFront(CharacterListObservation& entries) {
    return entries.front();
}
// This ordinary spelling retains the ambiguity of the short front() body.
struct OrdinaryCharacterFrontObservation {
    CharacterListObservation entries;
    CharacterValueObservation& First();
};
CharacterValueObservation& OrdinaryCharacterFrontObservation::First() {
    return *entries.begin();
}
extern const unsigned long CharacterFrontObservationSizes[] = {
    sizeof(CharacterValueObservation),sizeof(CharacterListObservation),
    sizeof(CharacterListObservation::iterator),
    sizeof(CharacterListObservation::const_iterator),
    sizeof(OrdinaryCharacterFrontObservation)
};
