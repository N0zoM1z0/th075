// Complete generic values observe widths, not original game declarations.
#include <deque>

template<unsigned N> struct EndValue { unsigned char bytes[N]; };

template<class Container> struct ManualEnds : Container {
    typename Container::reference first() { return *this->begin(); }
    typename Container::reference last() { return *(this->end() - 1); }
    typename Container::reference lastByDecrement() {
        typename Container::iterator previous = this->end();
        --previous;
        return *previous;
    }
};

#define ENDS(N) \
EndValue<N>& Front##N(std::deque<EndValue<N> >& values) { return values.front(); } \
EndValue<N>& Back##N(std::deque<EndValue<N> >& values) { return values.back(); } \
const EndValue<N>& ConstFront##N(const std::deque<EndValue<N> >& values) { return values.front(); } \
const EndValue<N>& ConstBack##N(const std::deque<EndValue<N> >& values) { return values.back(); } \
EndValue<N>& ManualFront##N(ManualEnds<std::deque<EndValue<N> > >& values) { return values.first(); } \
EndValue<N>& ManualBack##N(ManualEnds<std::deque<EndValue<N> > >& values) { return values.last(); } \
EndValue<N>& PreviousEnd##N(ManualEnds<std::deque<EndValue<N> > >& values) { \
    return values.lastByDecrement(); \
}

ENDS(4)
ENDS(8)
ENDS(64)

extern "C" const unsigned EndPublicLayout[] = {
    sizeof(EndValue<4>), sizeof(EndValue<8>), sizeof(EndValue<64>),
    sizeof(std::deque<EndValue<4> >), sizeof(std::deque<EndValue<8> >),
    sizeof(std::deque<EndValue<64> >), sizeof(std::deque<EndValue<4> >::iterator),
    sizeof(std::deque<EndValue<4> >::const_iterator), sizeof(unsigned), sizeof(void*)
};
