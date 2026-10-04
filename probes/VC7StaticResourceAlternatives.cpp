// Small complete observations test source operations without recovering game layouts.
#include <deque>
#include <vector>
#include <new>
extern "C" __declspec(dllimport) int __stdcall CloseStaticObservedHandle(void*);
template<unsigned Width> struct StaticValueObservation { unsigned char bytes[Width]; };
typedef std::deque<StaticValueObservation<1> > StaticByteDeque;
typedef std::deque<StaticValueObservation<2> > StaticWordDeque;
typedef std::deque<StaticValueObservation<4> > StaticDwordDeque;
struct ExplicitStaticQueuesObservation {
    void* handle;
    StaticByteDeque first;
    StaticWordDeque second;
    StaticByteDeque third;
    StaticDwordDeque fourth;
    ExplicitStaticQueuesObservation() { handle = 0; }
    void clearQueues() { first.clear(); second.clear(); third.clear(); fourth.clear(); }
    ~ExplicitStaticQueuesObservation() {
        clearQueues();
        if (handle) { CloseStaticObservedHandle(handle); handle = 0; }
    }
};
struct ImplicitStaticQueuesObservation {
    void* handle;
    StaticByteDeque first;
    StaticWordDeque second;
    StaticByteDeque third;
    StaticDwordDeque fourth;
};
void ConstructExplicitStaticQueues(ExplicitStaticQueuesObservation* p) { new (p) ExplicitStaticQueuesObservation; }
void ConstructImplicitStaticQueues(ImplicitStaticQueuesObservation* p) { new (p) ImplicitStaticQueuesObservation; }
void DestroyExplicitStaticQueues(ExplicitStaticQueuesObservation* p) { p->~ExplicitStaticQueuesObservation(); }
void DestroyImplicitStaticQueues(ImplicitStaticQueuesObservation* p) { p->~ImplicitStaticQueuesObservation(); }
struct StaticDeleteObservation { ~StaticDeleteObservation(); unsigned long value; };
typedef std::vector<StaticDeleteObservation*> StaticOwnedVector;
struct StaticTextureObservation { ~StaticTextureObservation(); };
struct ExplicitStaticPointerOwnerObservation {
    StaticDwordDeque queues[2];
    StaticTextureObservation textures;
    StaticOwnedVector pointers;
    void releaseEntries();
    ~ExplicitStaticPointerOwnerObservation() {
        releaseEntries();
        for (unsigned index = 0; index < pointers.size(); ++index)
            if (pointers[index]) delete pointers[index];
        pointers.clear();
    }
};
struct ImplicitStaticPointerOwnerObservation {
    StaticDwordDeque queues[2];
    StaticTextureObservation textures;
    StaticOwnedVector pointers;
};
void DestroyExplicitStaticPointerOwner(ExplicitStaticPointerOwnerObservation* p) { p->~ExplicitStaticPointerOwnerObservation(); }
void DestroyImplicitStaticPointerOwner(ImplicitStaticPointerOwnerObservation* p) { p->~ImplicitStaticPointerOwnerObservation(); }
struct OrdinaryStaticVectorIndexObservation {
    std::allocator<StaticDeleteObservation*> allocator;
    StaticDeleteObservation** first;
    StaticDeleteObservation** last;
    StaticDeleteObservation** capacity_end;
    StaticOwnedVector::iterator begin() { return StaticOwnedVector::iterator(first); }
    StaticDeleteObservation*& entry(unsigned index) { return *(begin() + index); }
};
struct OrdinaryStaticIteratorObservation : StaticOwnedVector::const_iterator {
    StaticDeleteObservation*& value() const {
        return const_cast<StaticDeleteObservation*&>(StaticOwnedVector::const_iterator::operator*());
    }
};
struct OrdinaryStaticVectorTidyObservation {
    unsigned long observed_words[4];
    void tidy();
    void clean() { tidy(); }
};
StaticDeleteObservation*& ObserveOrdinaryStaticIndex(OrdinaryStaticVectorIndexObservation& p, unsigned index) { return p.entry(index); }
StaticDeleteObservation*& ObserveOrdinaryStaticIterator(const OrdinaryStaticIteratorObservation& p) { return p.value(); }
void ObserveOrdinaryStaticTidy(OrdinaryStaticVectorTidyObservation& p) { p.clean(); }
extern "C" const unsigned long StaticResourceLayout[] = {
    sizeof(StaticByteDeque),sizeof(StaticWordDeque),sizeof(StaticDwordDeque),
    sizeof(ExplicitStaticQueuesObservation),sizeof(ImplicitStaticQueuesObservation),
    sizeof(StaticDeleteObservation),sizeof(StaticOwnedVector),
    sizeof(ExplicitStaticPointerOwnerObservation),sizeof(ImplicitStaticPointerOwnerObservation),
    sizeof(OrdinaryStaticVectorIndexObservation),sizeof(OrdinaryStaticIteratorObservation),
    sizeof(OrdinaryStaticVectorTidyObservation)
};
