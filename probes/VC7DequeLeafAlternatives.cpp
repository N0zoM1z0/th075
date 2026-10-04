// Complete observations and ordinary controls do not recover game declarations.
#include "VC7PairedDequeProducers.cpp"

struct OrdinaryCapacityObservation {
    size_t max_size() const {
        size_t count = static_cast<size_t>(-1) / sizeof(FileRecordObservation);
        return count > 0 ? count : 1;
    }
};

size_t ObserveOrdinaryCapacity(const OrdinaryCapacityObservation& value) {
    return value.max_size();
}

void OrdinaryDestroyInner(InnerRecordObservation* value) {
    value->~InnerRecordObservation();
}

void OrdinaryPlacementNoop(void*, void*) {}

extern "C" const unsigned long DequeLeafLayout[] = {
    sizeof(InnerRecordObservation), sizeof(QueueRecordObservation), sizeof(FileRecordObservation),
    sizeof(QueueRecordDeque), sizeof(FileRecordDeque), sizeof(QueueRecordDeque::size_type),
    sizeof(QueueRecordDeque::iterator), sizeof(FileRecordDeque::iterator),
    sizeof(OrdinaryCapacityObservation), sizeof(std::allocator<FileRecordObservation>)
};
