// Ordinary source alternatives retain the same complete SDK observation types.
// These are compiler controls, not recovered game declarations or exact units.
#include "VC7PairedDequeProducers.cpp"

QueueRecordObservation* AllocateQueueOrdinary(size_t count, QueueRecordObservation*) {
    return static_cast<QueueRecordObservation*>(operator new(count * sizeof(QueueRecordObservation)));
}
FileRecordObservation* AllocateFileOrdinary(size_t count, FileRecordObservation*) {
    return static_cast<FileRecordObservation*>(operator new(count * sizeof(FileRecordObservation)));
}
void ConstructQueueOrdinary(QueueRecordObservation* destination, const QueueRecordObservation& value) {
    new (static_cast<void*>(destination)) QueueRecordObservation(value);
}
void ConstructFileOrdinary(FileRecordObservation* destination, const FileRecordObservation& value) {
    new (static_cast<void*>(destination)) FileRecordObservation(value);
}
