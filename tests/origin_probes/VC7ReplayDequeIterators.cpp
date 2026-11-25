// Complete SDK observations; original replay element declarations remain unknown.
#include <deque>

#define OBSERVE_REPLAY_ITERATORS(T, N) \
    typedef std::deque<T> ReplayDeque##N; \
    void ObserveReplayDeque##N(ReplayDeque##N& entries) { \
        ReplayDeque##N::iterator current; \
        ReplayDeque##N::iterator last; \
        current = entries.begin(); \
        last = entries.end(); \
        while (current != last) { \
            (void)*current; \
            current++; \
        } \
    }
OBSERVE_REPLAY_ITERATORS(unsigned char, Byte)
OBSERVE_REPLAY_ITERATORS(unsigned short, Word)
OBSERVE_REPLAY_ITERATORS(unsigned long, Dword)

// Entire ordinary alternatives expose ambiguity of constructor bytes alone.
struct OrdinaryReplayConstIterator {
    void* owner;
    unsigned position;
    OrdinaryReplayConstIterator() : owner(0), position(0) {}
};
struct OrdinaryReplayIterator : OrdinaryReplayConstIterator {
    OrdinaryReplayIterator() : OrdinaryReplayConstIterator() {}
};
void ObserveOrdinaryReplayIterator() { OrdinaryReplayIterator current; }
extern "C" const unsigned long ReplayIteratorLayout[] = {
    sizeof(unsigned char), sizeof(unsigned short), sizeof(unsigned long),
    sizeof(ReplayDequeByte), sizeof(ReplayDequeWord), sizeof(ReplayDequeDword),
    sizeof(ReplayDequeByte::iterator), sizeof(ReplayDequeWord::iterator),
    sizeof(ReplayDequeDword::iterator), sizeof(ReplayDequeByte::const_iterator),
    sizeof(OrdinaryReplayIterator), sizeof(OrdinaryReplayConstIterator)
};
