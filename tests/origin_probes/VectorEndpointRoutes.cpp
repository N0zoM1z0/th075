#include <vector>

template<int N> struct EndpointValue { unsigned char bytes[N]; };
template<class Container> struct OrdinaryEndpoints : Container {
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;
    iterator mutableBegin() { return iterator(this->_Myfirst); }
    iterator mutableEnd() { return iterator(this->_Mylast); }
    const_iterator constBegin() const { return const_iterator(this->_Myfirst); }
    const_iterator constEnd() const { return const_iterator(this->_Mylast); }
};

#define ENDPOINTS(N) \
 std::vector<EndpointValue<N> >::iterator endpointBegin##N(std::vector<EndpointValue<N> >& v) { return v.begin(); } \
 std::vector<EndpointValue<N> >::iterator endpointEnd##N(std::vector<EndpointValue<N> >& v) { return v.end(); } \
 std::vector<EndpointValue<N> >::const_iterator endpointConstBegin##N(const std::vector<EndpointValue<N> >& v) { return v.begin(); } \
 std::vector<EndpointValue<N> >::const_iterator endpointConstEnd##N(const std::vector<EndpointValue<N> >& v) { return v.end(); }
ENDPOINTS(4)
ENDPOINTS(116)
ENDPOINTS(16)

#define ORDINARY(N) \
 OrdinaryEndpoints<std::vector<EndpointValue<N> > >::iterator ordinaryBegin##N(OrdinaryEndpoints<std::vector<EndpointValue<N> > >& v) { return v.mutableBegin(); } \
 OrdinaryEndpoints<std::vector<EndpointValue<N> > >::iterator ordinaryEnd##N(OrdinaryEndpoints<std::vector<EndpointValue<N> > >& v) { return v.mutableEnd(); } \
 OrdinaryEndpoints<std::vector<EndpointValue<N> > >::const_iterator ordinaryConstBegin##N(const OrdinaryEndpoints<std::vector<EndpointValue<N> > >& v) { return v.constBegin(); } \
 OrdinaryEndpoints<std::vector<EndpointValue<N> > >::const_iterator ordinaryConstEnd##N(const OrdinaryEndpoints<std::vector<EndpointValue<N> > >& v) { return v.constEnd(); }
ORDINARY(4)
ORDINARY(116)
ORDINARY(16)

extern const unsigned long EndpointPublicLayout[] = {
    sizeof(EndpointValue<4>), sizeof(EndpointValue<116>), sizeof(EndpointValue<16>),
    sizeof(std::vector<EndpointValue<4> >), sizeof(std::vector<EndpointValue<116> >), sizeof(std::vector<EndpointValue<16> >),
    sizeof(std::vector<EndpointValue<4> >::iterator), sizeof(std::vector<EndpointValue<4> >::const_iterator),
    sizeof(OrdinaryEndpoints<std::vector<EndpointValue<4> > >)
};
