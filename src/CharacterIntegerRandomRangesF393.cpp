#include <stdlib.h>
// Two independently authored native 44-byte game random range policies.
// Recovered original integer evaluation order is (maximum-minimum)*rand():
// original VC7.1 carries signed range in ESI across CRT rand.
// Independent original game addresses and native rand references checked.
// These are borrowed receiver interfaces, not an invented owner layout.
class CharacterAuxObjectF393 {public: int ChooseRange(int minimum,int maximum);};
class CharacterAIF393 {public: int ChooseRange(int minimum,int maximum);};
int CharacterAuxObjectF393::ChooseRange(int minimum,int maximum) {
    return (maximum-minimum)*rand()/32768 + minimum;
}
int CharacterAIF393::ChooseRange(int minimum,int maximum) {
    return (maximum-minimum)*rand()/32768 + minimum;
}
