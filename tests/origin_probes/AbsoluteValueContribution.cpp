// Ordinary expressions preserve ambiguity about an original CRT declaration.
#include <stdlib.h>

int OrdinaryAbsoluteInt(int value) {
    return value < 0 ? -value : value;
}

long OrdinaryAbsoluteLong(long value) {
    return value < 0 ? -value : value;
}

__int64 OrdinaryAbsoluteWide(__int64 value) {
    return value < 0 ? -value : value;
}

__int64 PublicAbsoluteWide(__int64 value) {
    return _abs64(value);
}

extern const unsigned long AbsoluteValueLayout[] = {
    sizeof(int), sizeof(long), sizeof(__int64)
};
