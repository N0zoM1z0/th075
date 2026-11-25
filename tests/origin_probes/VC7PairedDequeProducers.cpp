// Complete observation types test SDK emission; original game declarations remain unknown.
#include <deque>
#include <stddef.h>

struct InnerRecordObservation {
    unsigned char bytes[8];
    // This independently reviewed external policy does not recover a game declaration.
    ~InnerRecordObservation();
};
struct QueueRecordObservation { std::deque<InnerRecordObservation> values; };
struct FileRecordObservation { unsigned char bytes[60]; };

typedef std::deque<QueueRecordObservation> QueueRecordDeque;
typedef std::deque<FileRecordObservation> FileRecordDeque;

void AppendQueueRecord(QueueRecordDeque& queue, const QueueRecordObservation& value) {
    queue.push_back(value);
}
void AppendFileRecord(FileRecordDeque& queue, const FileRecordObservation& value) {
    queue.push_back(value);
}

extern "C" const unsigned long PairedDequeLayout[] = {
    sizeof(InnerRecordObservation), sizeof(QueueRecordObservation), sizeof(FileRecordObservation),
    sizeof(QueueRecordDeque), sizeof(FileRecordDeque), sizeof(QueueRecordDeque::size_type),
    sizeof(QueueRecordDeque::iterator), sizeof(FileRecordDeque::iterator)
};
