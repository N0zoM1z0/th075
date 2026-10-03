// Independent VC7.1 probe for complete deque algorithm template bodies.
// Synthetic widths do not identify the original game element types.
#include <deque>
#include <algorithm>

template<unsigned N> struct DequeAlgorithmRecord { unsigned char bytes[N]; };

#define PROBE_ALGORITHMS(T, N) \
  typedef T AlgorithmValue##N; \
  typedef std::deque<AlgorithmValue##N > AlgorithmDeque##N; \
  AlgorithmDeque##N::iterator ProbeCopy##N(AlgorithmDeque##N::iterator first, \
      AlgorithmDeque##N::iterator last, AlgorithmDeque##N::iterator out) { \
    return std::copy(first, last, out); \
  } \
  AlgorithmDeque##N::iterator ProbeCopyBackward##N(AlgorithmDeque##N::iterator first, \
      AlgorithmDeque##N::iterator last, AlgorithmDeque##N::iterator out) { \
    return std::copy_backward(first, last, out); \
  } \
  void ProbeFill##N(AlgorithmDeque##N::iterator first, AlgorithmDeque##N::iterator last, \
      const AlgorithmValue##N& value) { std::fill(first, last, value); } \
  void ProbeFillN##N(AlgorithmDeque##N::iterator first, \
      unsigned count, const AlgorithmValue##N& value) { \
    std::fill_n(first, count, value); \
  }

PROBE_ALGORITHMS(DequeAlgorithmRecord<1>, 1)
PROBE_ALGORITHMS(DequeAlgorithmRecord<2>, 2)
PROBE_ALGORITHMS(DequeAlgorithmRecord<4>, 4)
PROBE_ALGORITHMS(DequeAlgorithmRecord<8>, 8)
PROBE_ALGORITHMS(DequeAlgorithmRecord<16>, 16)
PROBE_ALGORITHMS(DequeAlgorithmRecord<32>, 32)
PROBE_ALGORITHMS(DequeAlgorithmRecord<64>, 64)

PROBE_ALGORITHMS(unsigned char, Byte)
PROBE_ALGORITHMS(unsigned short, Word)
PROBE_ALGORITHMS(unsigned long, Dword)
PROBE_ALGORITHMS(float, Float)
PROBE_ALGORITHMS(double, Double)
PROBE_ALGORITHMS(void*, Pointer)
