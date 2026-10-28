#include <windows.h>
#include <stdlib.h>
// Borrowed native 8-byte iterator ABI and 20-byte side-list receiver;
// implementation and private STL-style owner layout remain unproven.
// The four genuinely used contiguous state members capture native EBP slots:
// removed -0x20, 8-byte end -0x1c, index -0x14, count -0x10.
// EndInto is only the caller-side name for native End with its real hidden
// return-object pointer (005F80E0); no extra
// native method is invented or emitted here.
class EffectChildF297 {
public:
 virtual void Initialize();
 virtual void Advance();
};
class EffectIteratorF297 {
 unsigned int actualNativeWords[2];
public:
 bool operator!=(const EffectIteratorF297&) const;
 EffectChildF297*& operator*() const;
 EffectIteratorF297 operator++(int);
};
typedef char VerifyEffectIterator8F297[(sizeof(EffectIteratorF297)==8)?1:-1];
class EffectListF297 {
public:
 int Size();
 EffectChildF297** At(int index);
 EffectIteratorF297 Begin();
 EffectIteratorF297* EndInto(EffectIteratorF297* out);
 EffectIteratorF297 Erase(EffectIteratorF297 position);
};
class AuxEffectManagerF297 {
public:
 void AdvanceAndPruneTwoLists();
};
#define LIST(side) (reinterpret_cast<EffectListF297*>(reinterpret_cast<unsigned char*>(this)+(side)*0x14))
void AuxEffectManagerF297::AdvanceAndPruneTwoLists()
{
 struct IndexCountF298 {void* removed; EffectIteratorF297 end; int index; int count; };
 for (int side=0; side<2; ++side) {
   IndexCountF298 state;
   state.count=LIST(side)->Size();
   for (state.index=0; state.index<state.count; ++state.index) {
      LIST(side)->At(state.index)[0]->Advance();
   }
   EffectIteratorF297 iterator=LIST(side)->Begin();
   while (iterator!=*LIST(side)->EndInto(&state.end)) {
      if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(*iterator)+8)==0) {
         state.removed=*iterator;
         free(state.removed);
         iterator=LIST(side)->Erase(iterator);
      } else {
         iterator++;
      }
   }
 }
}
#undef LIST
