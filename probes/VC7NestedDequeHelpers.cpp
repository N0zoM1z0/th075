// Complete SDK source families; original game element types and folding remain unknown.
#include <deque>
#include <stddef.h>
template<unsigned N> struct HelperRecord { unsigned char bytes[N]; };
#define HELPER_CONTROLS(T, N) \
    typedef T HelperElement##N; \
    typedef std::deque<T > HelperQueue##N; \
    HelperElement##N& Back##N(HelperQueue##N& q) { return q.back(); } \
    HelperElement##N& MutableDereference##N(const HelperQueue##N::iterator& i) { return *i; } \
    const HelperElement##N& ConstDereference##N(const HelperQueue##N::const_iterator& i) { return *i; } \
    HelperQueue##N::iterator& SubtractAssign##N(HelperQueue##N::iterator& i, int delta) { return i -= delta; }
HELPER_CONTROLS(unsigned char, Byte)
HELPER_CONTROLS(unsigned short, Word)
HELPER_CONTROLS(unsigned long, Dword)
HELPER_CONTROLS(void*, Pointer)
HELPER_CONTROLS(HelperRecord<8>, 8)
HELPER_CONTROLS(HelperRecord<16>, 16)
HELPER_CONTROLS(HelperRecord<20>, 20)
HELPER_CONTROLS(HelperRecord<24>, 24)
HELPER_CONTROLS(HelperRecord<32>, 32)
HELPER_CONTROLS(HelperRecord<64>, 64)
HELPER_CONTROLS(std::deque<unsigned char>, NestedByte)
HELPER_CONTROLS(std::deque<unsigned short>, NestedWord)
HELPER_CONTROLS(std::deque<void*>, NestedPointer)
extern "C" const unsigned long NestedHelperLayout[] = {
    sizeof(std::deque<unsigned char>), sizeof(std::deque<unsigned short>),
    sizeof(std::deque<void*>), sizeof(HelperRecord<20>),
    sizeof(std::deque<std::deque<unsigned char> >),
    sizeof(std::deque<std::deque<unsigned char> >::iterator),
    sizeof(std::deque<std::deque<unsigned char> >::const_iterator),
    sizeof(std::deque<std::deque<unsigned char> >::difference_type)
};
