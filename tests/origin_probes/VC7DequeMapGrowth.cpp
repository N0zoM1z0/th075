// Cold VC7.1 source probe for generic deque map growth.
// Record widths test compiler/STL emission; they do not identify game types.
#include <deque>

template<unsigned N> struct DequeProbeRecord { unsigned char bytes[N]; };

#define PROBE_DEQUE(N) \
  std::deque<DequeProbeRecord<N> > probe_deque_##N; \
  void ProbeDeque##N(const DequeProbeRecord<N>& value) { \
    probe_deque_##N.push_front(value); \
    probe_deque_##N.push_back(value); \
    probe_deque_##N.pop_front(); \
    probe_deque_##N.pop_back(); \
  }

PROBE_DEQUE(1)
PROBE_DEQUE(2)
PROBE_DEQUE(4)
PROBE_DEQUE(8)
PROBE_DEQUE(16)
PROBE_DEQUE(32)
PROBE_DEQUE(64)
