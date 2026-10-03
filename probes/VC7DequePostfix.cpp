// Independent VC7 postfix overload probe; original element types remain unknown.
#include <deque>
template<unsigned N> struct PostfixRecord { unsigned char bytes[N]; };
#define PROBE_POSTFIX(T, N) \
  typedef T PostfixValue##N; \
  typedef std::deque<PostfixValue##N > PostfixDeque##N; \
  PostfixDeque##N::iterator PostIncrement##N(PostfixDeque##N::iterator& current) { return current++; } \
  PostfixDeque##N::iterator PostDecrement##N(PostfixDeque##N::iterator& current) { return current--; }
PROBE_POSTFIX(PostfixRecord<1>, 1)
PROBE_POSTFIX(PostfixRecord<2>, 2)
PROBE_POSTFIX(PostfixRecord<4>, 4)
PROBE_POSTFIX(PostfixRecord<8>, 8)
PROBE_POSTFIX(PostfixRecord<16>, 16)
PROBE_POSTFIX(PostfixRecord<32>, 32)
PROBE_POSTFIX(PostfixRecord<64>, 64)
PROBE_POSTFIX(unsigned char, Byte)
PROBE_POSTFIX(unsigned short, Word)
PROBE_POSTFIX(unsigned long, Dword)
PROBE_POSTFIX(float, Float)
PROBE_POSTFIX(double, Double)
PROBE_POSTFIX(void*, Pointer)
