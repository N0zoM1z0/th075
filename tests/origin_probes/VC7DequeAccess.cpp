// Independent VC7.1 probe for bounds-checked deque indexing.
// Width variants test STL emission, not the game's original element types.
#include <deque>

template<unsigned N> struct DequeAccessRecord { unsigned char bytes[N]; };

#define PROBE_ACCESS(N) \
  std::deque<DequeAccessRecord<N> > access_deque_##N; \
  DequeAccessRecord<N>& ProbeAccess##N(unsigned index) { \
    return access_deque_##N.at(index); \
  }

PROBE_ACCESS(1)
PROBE_ACCESS(2)
PROBE_ACCESS(4)
PROBE_ACCESS(8)
PROBE_ACCESS(16)
PROBE_ACCESS(32)
PROBE_ACCESS(64)
