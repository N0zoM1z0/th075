// The character value width is an observation, not a recovered entry declaration.
#include "VC7ArchiveListPolicies.cpp"

struct CharacterValueObservation { unsigned char bytes[16]; };
typedef std::list<CharacterValueObservation> CharacterListObservation;
void ObserveCharacterList(CharacterListObservation& entries, const CharacterValueObservation& value) {
    if (entries.size()) {
        CharacterListObservation::iterator current = entries.begin();
        CharacterListObservation::iterator last = entries.end();
        if (current != last) entries.push_back(value);
    }
}
extern "C" const unsigned long CharacterListLayout[] = {
    sizeof(CharacterValueObservation), sizeof(CharacterListObservation),
    sizeof(CharacterListObservation::iterator)
};
