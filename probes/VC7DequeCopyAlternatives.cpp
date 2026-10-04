// Complete observations test implicit/explicit copy ownership; game types remain unknown.
#include "VC7PairedDequeProducers.cpp"

struct ExplicitQueueRecordObservation {
    std::deque<InnerRecordObservation> values;
    ExplicitQueueRecordObservation(const ExplicitQueueRecordObservation& other)
        : values(other.values) {}
};

void CopyImplicitQueueRecord(QueueRecordObservation* destination, const QueueRecordObservation& value) {
    new (static_cast<void*>(destination)) QueueRecordObservation(value);
}
void CopyExplicitQueueRecord(ExplicitQueueRecordObservation* destination, const ExplicitQueueRecordObservation& value) {
    new (static_cast<void*>(destination)) ExplicitQueueRecordObservation(value);
}

extern "C" const unsigned long CopyObservationLayout[] = {
    sizeof(QueueRecordObservation), sizeof(ExplicitQueueRecordObservation),
    sizeof(std::deque<InnerRecordObservation>), sizeof(InnerRecordObservation)
};
