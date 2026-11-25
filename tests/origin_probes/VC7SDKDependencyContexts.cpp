// Complete synthetic observations test SDK operations, not original game declarations.
#include <deque>
#include <algorithm>
#include <memory>

struct TwoByteObservation { unsigned char bytes[2]; };
struct Queue20Observation {
    unsigned char bytes[20];
    ~Queue20Observation();
};
struct File60Observation { unsigned char bytes[60]; };
struct Copy116Observation {
    unsigned char bytes[116];
    Copy116Observation(const Copy116Observation&);
    Copy116Observation& operator=(const Copy116Observation&);
};

unsigned ObserveMax(const std::deque<TwoByteObservation>& values) { return values.max_size(); }
void ObserveQueuePop(std::deque<Queue20Observation>& values) { values.pop_back(); }
void ObserveQueueClear(std::deque<Queue20Observation>& values) { values.clear(); }
void ObserveFilePop(std::deque<File60Observation>& values) { values.pop_back(); }
void ObserveFileClear(std::deque<File60Observation>& values) { values.clear(); }
Copy116Observation* ObserveCopy(Copy116Observation* first, Copy116Observation* last, Copy116Observation* dest) {
    return std::copy(first, last, dest);
}
Copy116Observation* ObserveCopyBackward(Copy116Observation* first, Copy116Observation* last, Copy116Observation* dest) {
    return std::copy_backward(first, last, dest);
}
void ObserveConstruct(std::allocator<Copy116Observation>& allocator,
                      Copy116Observation* dest, const Copy116Observation& value) {
    allocator.construct(dest, value);
}

struct OrdinaryCapacityObservation {
    size_t capacity() const {
        size_t count = static_cast<size_t>(-1) / sizeof(TwoByteObservation);
        return count > 0 ? count : 1;
    }
};
unsigned ObserveOrdinaryCapacity(const OrdinaryCapacityObservation& value) { return value.capacity(); }

template<class T> struct OrdinaryDequeObservation {
    std::allocator<T*> map_allocator;
    std::allocator<T> value_allocator;
    T** map;
    unsigned map_count;
    unsigned offset;
    unsigned size;
    enum { block_capacity = sizeof(T) <= 1 ? 16 : sizeof(T) <= 2 ? 8 :
                            sizeof(T) <= 4 ? 4 : sizeof(T) <= 8 ? 2 : 1 };
    bool empty() const { return size == 0; }
    void popBack() {
        if (!empty()) {
            unsigned new_offset = size + offset - 1;
            unsigned block = new_offset / block_capacity;
            if (map_count <= block)
                block -= map_count;
            value_allocator.destroy(map[block] + new_offset % block_capacity);
            if (--size == 0)
                offset = 0;
        }
    }
};
void ObserveOrdinaryQueuePop(OrdinaryDequeObservation<Queue20Observation>& values) { values.popBack(); }
void ObserveOrdinaryFilePop(OrdinaryDequeObservation<File60Observation>& values) { values.popBack(); }
Copy116Observation* OrdinaryCopy(Copy116Observation* first, Copy116Observation* last,
                                 Copy116Observation* dest, std::_Nonscalar_ptr_iterator_tag) {
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}
void OrdinaryConstruct(Copy116Observation* dest, const Copy116Observation& value) {
    ::new (static_cast<void*>(dest)) Copy116Observation(value);
}

extern "C" const unsigned long SDKDependencyLayout[] = {
    sizeof(TwoByteObservation), sizeof(Queue20Observation), sizeof(File60Observation), sizeof(Copy116Observation),
    sizeof(std::deque<TwoByteObservation>), sizeof(std::deque<Queue20Observation>), sizeof(std::deque<File60Observation>),
    sizeof(std::allocator<TwoByteObservation>), sizeof(std::allocator<Queue20Observation>),
    sizeof(std::allocator<File60Observation>), sizeof(std::allocator<Copy116Observation>),
    sizeof(OrdinaryCapacityObservation), sizeof(OrdinaryDequeObservation<Queue20Observation>),
    sizeof(OrdinaryDequeObservation<File60Observation>), sizeof(std::_Nonscalar_ptr_iterator_tag)
};
