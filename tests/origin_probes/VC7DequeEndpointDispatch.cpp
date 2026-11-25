// Actual SDK dispatch controls use complete observations, not recovered game declarations.
#include "VC7PairedDequeProducers.cpp"

typedef std::deque<InnerRecordObservation> InnerRecordDeque;
typedef InnerRecordDeque::const_iterator InnerConstIterator;
struct InputCategoryTraitsObservation : std::iterator<std::input_iterator_tag, InnerRecordObservation> {};
struct ForwardCategoryTraitsObservation : std::iterator<std::forward_iterator_tag, InnerRecordObservation> {};
struct BidirectionalCategoryTraitsObservation : std::iterator<std::bidirectional_iterator_tag, InnerRecordObservation> {};

std::input_iterator_tag ObserveInputCategory(const InputCategoryTraitsObservation& value) {
    return std::_Iter_cat(value);
}
std::bidirectional_iterator_tag ObserveBidirectionalCategory(const BidirectionalCategoryTraitsObservation& value) {
    return std::_Iter_cat(value);
}
std::forward_iterator_tag ObserveForwardCategory(const ForwardCategoryTraitsObservation& value) {
    return std::_Iter_cat(value);
}
void ObserveInputDistance(InnerConstIterator first, InnerConstIterator last, unsigned int& offset) {
    std::_Distance2(first, last, offset, std::input_iterator_tag());
}
void ObserveBidirectionalAdvance(InnerConstIterator& value, unsigned int offset) {
    std::_Advance(value, offset, std::bidirectional_iterator_tag());
}

extern "C" const unsigned long EndpointDispatchLayout[] = {
    sizeof(InnerRecordDeque), sizeof(InnerConstIterator), sizeof(InnerRecordDeque::difference_type),
    sizeof(InputCategoryTraitsObservation), sizeof(BidirectionalCategoryTraitsObservation),
    sizeof(std::input_iterator_tag), sizeof(std::bidirectional_iterator_tag), sizeof(std::random_access_iterator_tag),
    sizeof(ForwardCategoryTraitsObservation), sizeof(std::forward_iterator_tag)
};
