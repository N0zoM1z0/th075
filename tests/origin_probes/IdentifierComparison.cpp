// Ordinary storage equality does not identify an original GUID or owner.
#include <string.h>

struct OrdinaryIdentifier {
    unsigned long words[4];
};

bool EqualOrdinaryIdentifier(const OrdinaryIdentifier& left,
                             const OrdinaryIdentifier& right) {
    return memcmp(&left, &right, sizeof(OrdinaryIdentifier)) == 0;
}

extern const unsigned long IdentifierComparisonLayout[] = {
    sizeof(OrdinaryIdentifier), sizeof(unsigned long)
};
