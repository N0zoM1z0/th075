#include <deque>
#include <queue>
// Complete compact generic observations; no original replay-owner layout.
struct ReplayQueueObservation {
    void* fileHandle;
    std::deque<unsigned char> records;
    bool exhausted() const;
    bool active() const;
};
bool ReplayQueueObservation::exhausted() const {
    if (records.size() > 0) return false;
    return true;
}
bool ReplayQueueObservation::active() const { return fileHandle != 0; }
bool BorrowedReplayQueueExhausted(const std::deque<unsigned char>& records) {
    if (records.size() > 0) return false;
    return true;
}
bool ObservePublicReplayDequeEmpty(const std::deque<unsigned char>& records) {
    return records.empty();
}
typedef std::queue<unsigned char, std::deque<unsigned char> > PublicReplayQueue;
bool ObservePublicReplayQueueEmpty(const PublicReplayQueue& records) {
    return records.empty();
}
extern const unsigned long ReplayQueueObservationSizes[] = {
    sizeof(ReplayQueueObservation), sizeof(std::deque<unsigned char>),
    sizeof(PublicReplayQueue), sizeof(std::deque<unsigned char>::size_type)
};
