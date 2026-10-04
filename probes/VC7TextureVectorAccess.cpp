// Complete synthetic 44-byte observation; original texture entry declaration is unknown.
#include <vector>
struct TextureAccessObservation {
    unsigned char bytes[44];
    ~TextureAccessObservation();
};
typedef std::vector<TextureAccessObservation> TextureAccessVector;
TextureAccessObservation& ObserveTextureIndex(TextureAccessVector& entries, unsigned index) {
    return entries[index];
}
TextureAccessVector::iterator ObserveTextureBegin(TextureAccessVector& entries) { return entries.begin(); }
TextureAccessVector::iterator ObserveTextureEnd(TextureAccessVector& entries) { return entries.end(); }
unsigned ObserveTextureSize(const TextureAccessVector& entries) { return entries.size(); }
TextureAccessVector::iterator ObserveTextureErase(TextureAccessVector& entries,
        TextureAccessVector::iterator first, TextureAccessVector::iterator last) {
    return entries.erase(first, last);
}
TextureAccessVector::iterator ObserveTextureAdd(const TextureAccessVector::iterator& current, int offset) {
    return current + offset;
}
// A complete ordinary owner can emit the same endpoint and index bodies.
struct OrdinaryTextureAccess {
    std::allocator<TextureAccessObservation> allocator;
    TextureAccessObservation* first;
    TextureAccessObservation* last;
    TextureAccessObservation* capacity_end;
    TextureAccessVector::iterator begin() { return TextureAccessVector::iterator(first); }
    TextureAccessVector::iterator end() { return TextureAccessVector::iterator(last); }
    TextureAccessObservation& entry(unsigned index) { return *(begin() + index); }
};
TextureAccessObservation& ObserveOrdinaryTextureIndex(OrdinaryTextureAccess& entries, unsigned index) {
    return entries.entry(index);
}
TextureAccessVector::iterator ObserveOrdinaryTextureBegin(OrdinaryTextureAccess& entries) { return entries.begin(); }
TextureAccessVector::iterator ObserveOrdinaryTextureEnd(OrdinaryTextureAccess& entries) { return entries.end(); }
extern "C" const unsigned long TextureAccessLayout[] = {
    sizeof(TextureAccessObservation), sizeof(TextureAccessVector),
    sizeof(TextureAccessVector::iterator), sizeof(TextureAccessVector::const_iterator),
    sizeof(OrdinaryTextureAccess), sizeof(std::allocator<TextureAccessObservation>)
};
