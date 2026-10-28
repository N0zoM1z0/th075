// Native complete 112-byte card-list owner cleanup: genuine offset+0x18
// vector of allocated card data pointers, 32-bit index and actual free temp.
class CardPointersF490 {
public:unsigned int Size();void** At(unsigned int);void Clear();
};
extern void __cdecl DeleteCardPointerAt0064169D(void*);
class CardListF490 {
 unsigned char nativeOwnerPrefixBytes[0x18];
 CardPointersF490 members;
public:void ClearEntries();
};
void CardListF490::ClearEntries() {
 for (unsigned int index=0;index<members.Size();++index) {
    if (*members.At(index)) {
       void* owned = *members.At(index);
       DeleteCardPointerAt0064169D(owned);
    }
 }
 members.Clear();
}
