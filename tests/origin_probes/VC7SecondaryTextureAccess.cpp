// Complete SDK and ordinary observations; original resource declarations stay unknown.
#include <vector>
struct SecondaryTextureAccessObservation { unsigned char bytes[4]; };
typedef std::vector<SecondaryTextureAccessObservation> SecondaryTextureVector;
SecondaryTextureAccessObservation& ObserveSecondaryTextureIndex(SecondaryTextureVector& entries, unsigned index) {
    return entries[index];
}
struct OrdinarySecondaryTextureAccess {
    std::allocator<SecondaryTextureAccessObservation> allocator;
    SecondaryTextureAccessObservation* first;
    SecondaryTextureAccessObservation* last;
    SecondaryTextureAccessObservation* capacity_end;
    SecondaryTextureVector::iterator begin() { return SecondaryTextureVector::iterator(first); }
    SecondaryTextureAccessObservation& entry(unsigned index) { return *(begin() + index); }
};
SecondaryTextureAccessObservation& ObserveOrdinarySecondaryTextureIndex(OrdinarySecondaryTextureAccess& entries, unsigned index) {
    return entries.entry(index);
}
struct OrdinarySecondaryTextureIterator : SecondaryTextureVector::const_iterator {
    SecondaryTextureAccessObservation& value() const {
        return const_cast<SecondaryTextureAccessObservation&>(SecondaryTextureVector::const_iterator::operator*());
    }
};
SecondaryTextureAccessObservation& ObserveOrdinarySecondaryTextureValue(const OrdinarySecondaryTextureIterator& current) {
    return current.value();
}
extern "C" const unsigned long SecondaryTextureAccessLayout[] = {
    sizeof(SecondaryTextureAccessObservation), sizeof(SecondaryTextureVector),
    sizeof(SecondaryTextureVector::iterator), sizeof(SecondaryTextureVector::const_iterator),
    sizeof(OrdinarySecondaryTextureAccess), sizeof(OrdinarySecondaryTextureIterator)
};
