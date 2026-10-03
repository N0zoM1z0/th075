// Independent natural queue policy and vendor helper controls.
#include <deque>
extern std::deque<void*> queue_probe;
void QueueUnique(void* entry) {
    bool unique = true;
    for (int i = 0; i < queue_probe.size(); ++i) {
        if (queue_probe.at(i) == entry) unique = false;
    }
    if (unique) queue_probe.push_back(entry);
}
template<unsigned N> struct QueueRecord { unsigned char bytes[N]; };
#define QUEUE_HELPERS(T, N) \
    typedef std::deque<T > Queue##N; \
    Queue##N::iterator Default##N() { return Queue##N::iterator(); } \
    Queue##N::const_iterator ConstDefault##N() { return Queue##N::const_iterator(); } \
    Queue##N::size_type Size##N(Queue##N& q) { return q.size(); } \
    T& Unchecked##N(Queue##N& q, unsigned i) { return q[i]; } \
    T& Front##N(Queue##N& q) { return q.front(); } \
    T& Back##N(Queue##N& q) { return q.back(); } \
    Queue##N::iterator Begin##N(Queue##N& q) { return q.begin(); }
QUEUE_HELPERS(unsigned char, Byte)
QUEUE_HELPERS(unsigned short, Word)
QUEUE_HELPERS(unsigned long, Dword)
QUEUE_HELPERS(float, Float)
QUEUE_HELPERS(double, Double)
QUEUE_HELPERS(void*, Pointer)
QUEUE_HELPERS(QueueRecord<1>, 1)
QUEUE_HELPERS(QueueRecord<2>, 2)
QUEUE_HELPERS(QueueRecord<4>, 4)
QUEUE_HELPERS(QueueRecord<8>, 8)
QUEUE_HELPERS(QueueRecord<16>, 16)
QUEUE_HELPERS(QueueRecord<32>, 32)
QUEUE_HELPERS(QueueRecord<64>, 64)
