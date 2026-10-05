// Original public count controls; byte carriers do not recover private element types.
#include <deque>

void ObserveByteDequeAssign(std::deque<unsigned char>* values,
                            unsigned int count, const unsigned char& item) {
    values->assign(count, item);
}
void ObserveByteDequeInsert(std::deque<unsigned char>* values,
                            std::deque<unsigned char>::iterator position,
                            unsigned int count, const unsigned char& item) {
    values->insert(position, count, item);
}

extern const unsigned long ByteDequeCountLayout[] = {
    sizeof(unsigned char), sizeof(std::deque<unsigned char>),
    sizeof(std::deque<unsigned char>::iterator),
    sizeof(std::deque<unsigned char>::const_iterator)
};
