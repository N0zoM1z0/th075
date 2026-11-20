// Address-anchored natural-C++ alternative for the unreferenced 004135F0 leaf.
// Only the observed stores are modeled; the owner and preceding layout remain
// unknown, and this carrier is never instantiated as a complete game object.
class UnknownParameterBlockAt004135F0 {
    unsigned char unknown00[0x1c];
    unsigned int rawWordAt1C;
    unsigned int rawWordAt20;
    unsigned char rawByteAt24;
public:
    void StoreAt004135F0(unsigned char byteValue,
        unsigned int firstWord, unsigned int secondWord);
};

void UnknownParameterBlockAt004135F0::StoreAt004135F0(
    unsigned char byteValue, unsigned int firstWord, unsigned int secondWord)
{
    rawByteAt24 = byteValue;
    rawWordAt1C = firstWord;
    rawWordAt20 = secondWord;
}
