// Complete generic values observe the SDK; they do not declare game layouts.
#include <vector>
#include <deque>

template<unsigned N> struct IndexWords { unsigned long words[N]; };
template<unsigned N> struct IndexBytes { unsigned char bytes[N]; };

template<class Container> struct ManualIndexObservation : Container {
    typename Container::reference read(unsigned index) {
        return *(this->begin() + index);
    }
};

#define VECTOR_INDEX(N) \
IndexWords<N>& VectorIndex##N(std::vector<IndexWords<N> >& values, unsigned index) { \
    return values[index]; \
} \
IndexWords<N>& ManualVectorIndex##N(ManualIndexObservation<std::vector<IndexWords<N> > >& values, unsigned index) { \
    return values.read(index); \
} \
const IndexWords<N>& ConstVectorIndex##N(const std::vector<IndexWords<N> >& values, unsigned index) { \
    return values[index]; \
}

#define DEQUE_INDEX(N) \
IndexBytes<N>& DequeIndex##N(std::deque<IndexBytes<N> >& values, unsigned index) { \
    return values[index]; \
} \
IndexBytes<N>& ManualDequeIndex##N(ManualIndexObservation<std::deque<IndexBytes<N> > >& values, unsigned index) { \
    return values.read(index); \
} \
const IndexBytes<N>& ConstDequeIndex##N(const std::deque<IndexBytes<N> >& values, unsigned index) { \
    return values[index]; \
}

VECTOR_INDEX(1)
VECTOR_INDEX(4)
VECTOR_INDEX(29)
DEQUE_INDEX(1)
DEQUE_INDEX(4)
DEQUE_INDEX(60)

extern "C" const unsigned IndexPublicLayout[] = {
    sizeof(IndexWords<1>), sizeof(IndexWords<4>), sizeof(IndexWords<29>),
    sizeof(IndexBytes<1>), sizeof(IndexBytes<4>), sizeof(IndexBytes<60>),
    sizeof(std::vector<IndexWords<1> >), sizeof(std::vector<IndexWords<1> >::iterator),
    sizeof(std::vector<IndexWords<1> >::const_iterator),
    sizeof(std::deque<IndexBytes<1> >), sizeof(std::deque<IndexBytes<1> >::iterator),
    sizeof(std::deque<IndexBytes<1> >::const_iterator)
};
