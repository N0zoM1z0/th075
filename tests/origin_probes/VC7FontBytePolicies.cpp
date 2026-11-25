// Complete source observers do not recover the original font-owner layout.
#include <mbctype.h>
#include <new>

struct FontBytePolicyObservation {
    bool lead(unsigned char value) {
        if (value < 0x81) return false;
        if (value < 0xA0) return true;
        if (value < 0xE0) return false;
        if (value < 0xFF) return true;
        return false;
    }
    unsigned char decode(const signed char* input, int* output) {
        if (lead(static_cast<unsigned char>(input[0]))) {
            *output = (static_cast<unsigned char>(input[0]) << 8)
                | static_cast<unsigned char>(input[1]);
            return 2;
        }
        *output = input[0];
        return 1;
    }
};

struct OrdinaryLeadRangeObservation {
    bool classify(unsigned char value) {
        if (value < 0x81) return false;
        if (value < 0xA0) return true;
        if (value < 0xE0) return false;
        if (value < 0xFF) return true;
        return false;
    }
};

bool ObserveSDKLeadByte(unsigned char value) { return _ismbblead(value) != 0; }
bool ObserveOrdinaryLeadByte(OrdinaryLeadRangeObservation* owner, unsigned char value) {
    return owner->classify(value);
}
unsigned char ObserveFontBytePolicy(FontBytePolicyObservation* owner,
        const signed char* input, int* output) { return owner->decode(input, output); }

struct ExplicitFontResourceObservation {
    void* window;
    void* dc;
    unsigned width;
    void* previous_object;
    unsigned char* storage;
    explicit ExplicitFontResourceObservation(void* input_window) {
        window = input_window;
        dc = 0;
        width = 0;
        previous_object = 0;
        storage = 0;
    }
};
struct ImplicitFontResourceObservation {
    void* window;
    void* dc;
    unsigned width;
    void* previous_object;
    unsigned char* storage;
};
void ObserveExplicitFontResource(ExplicitFontResourceObservation* owner, void* window) {
    new (owner) ExplicitFontResourceObservation(window);
}
void ObserveImplicitFontResource(ImplicitFontResourceObservation* owner) {
    new (owner) ImplicitFontResourceObservation;
}
extern "C" const unsigned long FontBytePolicyLayout[] = {
    sizeof(FontBytePolicyObservation), sizeof(OrdinaryLeadRangeObservation),
    sizeof(ExplicitFontResourceObservation), sizeof(ImplicitFontResourceObservation),
    sizeof(unsigned char), sizeof(int)
};
