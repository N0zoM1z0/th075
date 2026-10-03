// Independent standard-library family probe; no original game type is inferred.
#include <deque>
template<unsigned N> struct EraseRecord { unsigned char bytes[N]; };
#define PROBE_ERASE(T, N) \
  typedef T EraseValue##N; \
  typedef std::deque<EraseValue##N > EraseDeque##N; \
  EraseDeque##N::iterator EraseRange##N(EraseDeque##N& values, \
      EraseDeque##N::iterator first, EraseDeque##N::iterator last) { \
      return values.erase(first, last); \
  } \
  EraseDeque##N::iterator EraseOne##N(EraseDeque##N& values, \
      EraseDeque##N::iterator where) { return values.erase(where); }
PROBE_ERASE(EraseRecord<1>, 1)
PROBE_ERASE(EraseRecord<2>, 2)
PROBE_ERASE(EraseRecord<4>, 4)
PROBE_ERASE(EraseRecord<8>, 8)
PROBE_ERASE(EraseRecord<16>, 16)
PROBE_ERASE(EraseRecord<32>, 32)
PROBE_ERASE(EraseRecord<64>, 64)
PROBE_ERASE(unsigned char, Byte)
PROBE_ERASE(unsigned short, Word)
PROBE_ERASE(unsigned long, Dword)
PROBE_ERASE(float, Float)
PROBE_ERASE(double, Double)
PROBE_ERASE(void*, Pointer)
