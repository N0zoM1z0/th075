// Complete original R109 114-byte game-specific selected side dispatch.
// The native source uses an actual for-loop with postfix increment of its
// 8-byte iterator, compares against borrowed 8-byte End(), and directly
// virtual-calls (*iterator)->Dispatch at vtable offset +8. Holding a named
// child local changes original EBP slots; direct dereference is required.
// The private list/iterator structures are borrowed ABI-only 8/20-byte views.
class EffectChildF395 {
public:
    virtual void Initialize();
    virtual void Release();
    virtual void Dispatch();
};
class EffectIteratorF395 {
    unsigned int nativeWords[2];
public:
    bool operator!=(const EffectIteratorF395&) const;
    EffectChildF395*& operator*() const;
    EffectIteratorF395 operator++(int);
};
typedef char CheckEightByteIteratorF395[(sizeof(EffectIteratorF395)==8)?1:-1];
class EffectListF395 {
public:
    EffectIteratorF395 Begin();
    EffectIteratorF395 End();
};
class AuxEffectManagerF395 {public:void DispatchSelectedList(signed char side);};
#define LIST(side) (*reinterpret_cast<EffectListF395*>(reinterpret_cast<unsigned char*>(this)+int(side)*20))
void AuxEffectManagerF395::DispatchSelectedList(signed char side) {
    EffectIteratorF395 current=LIST(side).Begin();
    EffectIteratorF395 end=LIST(side).End();
    for (; current!=end; current++) {
        (*current)->Dispatch();
    }
}
#undef LIST
