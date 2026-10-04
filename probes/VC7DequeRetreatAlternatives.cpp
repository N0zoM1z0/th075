// Complete synthetic width variants; original element declarations stay unknown.
#include <deque>
template<unsigned Width> struct RetreatValueObservation { unsigned char bytes[Width]; };
template<unsigned Width> struct OrdinaryRetreatObservation : std::deque<RetreatValueObservation<Width> >::iterator {
    typedef typename std::deque<RetreatValueObservation<Width> >::iterator Base;
    Base& retreat(int offset) { return Base::operator+=(-offset); }
};
#define OBSERVE_RETREAT(Width) \
typedef std::deque<RetreatValueObservation<Width> > RetreatDeque##Width; \
RetreatDeque##Width::iterator ObserveRetreat##Width(RetreatDeque##Width::iterator& current, int offset) { \
    current -= offset; return current - offset; \
} \
RetreatDeque##Width::iterator ObserveAddition##Width(const RetreatDeque##Width::iterator& current, int offset) { \
    return current + offset; \
} \
RetreatDeque##Width::iterator& ObserveOrdinaryRetreat##Width(OrdinaryRetreatObservation<Width>& current, int offset) { \
    return current.retreat(offset); \
}
OBSERVE_RETREAT(1)
OBSERVE_RETREAT(2)
OBSERVE_RETREAT(4)
OBSERVE_RETREAT(64)
extern "C" const unsigned long DequeRetreatLayout[] = {
    sizeof(RetreatValueObservation<1>),sizeof(RetreatValueObservation<2>),
    sizeof(RetreatValueObservation<4>),sizeof(RetreatValueObservation<64>),
    sizeof(RetreatDeque1::iterator),sizeof(RetreatDeque2::iterator),
    sizeof(RetreatDeque4::iterator),sizeof(RetreatDeque64::iterator),
    sizeof(OrdinaryRetreatObservation<1>),sizeof(OrdinaryRetreatObservation<2>),
    sizeof(OrdinaryRetreatObservation<4>),sizeof(OrdinaryRetreatObservation<64>)
};
