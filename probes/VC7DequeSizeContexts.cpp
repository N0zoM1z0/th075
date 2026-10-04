// Independent complete VC7 types and a synthetic observation model; no recovered game owner.
#include <deque>
#include <stddef.h>
template<unsigned N> struct SizeRecord { unsigned char bytes[N]; };
#define SIZE_CONTROL(T, N) \
    typedef std::deque<T > SizeQueue##N; \
    SizeQueue##N::size_type SizeControl##N(const SizeQueue##N& q) { return q.size(); }
SIZE_CONTROL(unsigned char, Byte)
SIZE_CONTROL(unsigned short, Word)
SIZE_CONTROL(unsigned long, Dword)
SIZE_CONTROL(float, Float)
SIZE_CONTROL(double, Double)
SIZE_CONTROL(void*, Pointer)
SIZE_CONTROL(SizeRecord<1>, 1)
SIZE_CONTROL(SizeRecord<2>, 2)
SIZE_CONTROL(SizeRecord<4>, 4)
SIZE_CONTROL(SizeRecord<8>, 8)
SIZE_CONTROL(SizeRecord<16>, 16)
SIZE_CONTROL(SizeRecord<32>, 32)
SIZE_CONTROL(SizeRecord<64>, 64)
// Actual complete SDK container and iterator records; original element types remain unknown.
extern "C" const unsigned long DequeSizeLayout[] = {
    sizeof(std::deque<unsigned char>), sizeof(std::deque<unsigned short>),
    sizeof(std::deque<unsigned long>), sizeof(std::deque<void*>),
    sizeof(std::deque<SizeRecord<64> >), sizeof(std::deque<unsigned char>::iterator),
    sizeof(std::deque<unsigned char>::const_iterator), sizeof(std::deque<unsigned char>::size_type)
};
