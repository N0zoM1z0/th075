// Independent VC7.1 probe for deque iterator operations and comparisons.
// Synthetic record widths test template emission, not original game types.
#include <deque>

template<unsigned N> struct DequeIteratorRecord { unsigned char bytes[N]; };

#define PROBE_ITERATORS(N) \
  std::deque<DequeIteratorRecord<N> > iterator_deque_##N; \
  bool ProbeIteratorEq##N() { \
    std::deque<DequeIteratorRecord<N> >::iterator first = iterator_deque_##N.begin(); \
    std::deque<DequeIteratorRecord<N> >::iterator last = iterator_deque_##N.end(); \
    return first == last; \
  } \
  bool ProbeIteratorLess##N() { \
    std::deque<DequeIteratorRecord<N> >::iterator first = iterator_deque_##N.begin(); \
    std::deque<DequeIteratorRecord<N> >::iterator last = iterator_deque_##N.end(); \
    return first < last; \
  } \
  unsigned ProbeIteratorDistance##N() { \
    std::deque<DequeIteratorRecord<N> >::iterator first = iterator_deque_##N.begin(); \
    std::deque<DequeIteratorRecord<N> >::iterator last = iterator_deque_##N.end(); \
    return last - first; \
  } \
  void ProbeIteratorStep##N() { \
    std::deque<DequeIteratorRecord<N> >::iterator it = iterator_deque_##N.begin(); \
    ++it; --it; it += 2; it -= 1; \
  }

PROBE_ITERATORS(1)
PROBE_ITERATORS(2)
PROBE_ITERATORS(4)
PROBE_ITERATORS(8)
PROBE_ITERATORS(16)
PROBE_ITERATORS(32)
PROBE_ITERATORS(64)
