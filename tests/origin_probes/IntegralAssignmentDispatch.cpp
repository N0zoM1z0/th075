#include <vector>
#include <deque>

void ObserveVectorIntegral(std::vector<unsigned long>& owner, int count, int value) {
    owner.assign(count, value);
}

void ObserveDequeIntegral(std::deque<unsigned char>& owner, int count, int value) {
    owner.assign(count, value);
}

template<class Container>
struct OrdinaryAssignment : Container {
    void dispatch(int count, int value) {
        this->_Assign(count, value, std::_Iter_cat(count));
    }

    void convert(int count, int value, std::_Int_iterator_tag) {
        this->_Assign_n((typename Container::size_type)count,
                        (typename Container::value_type)value);
    }
};

void ObserveOrdinaryVector(OrdinaryAssignment<std::vector<unsigned long> >& owner,
                           int count, int value, std::_Int_iterator_tag category) {
    owner.dispatch(count, value);
    owner.convert(count, value, category);
}

void ObserveOrdinaryDeque(OrdinaryAssignment<std::deque<unsigned char> >& owner,
                          int count, int value, std::_Int_iterator_tag category) {
    owner.dispatch(count, value);
    owner.convert(count, value, category);
}

void ObserveVectorRange(std::vector<unsigned long>& owner,
                        const unsigned long* first, const unsigned long* last) {
    owner.assign(first, last);
}

void ObserveDequeRange(std::deque<unsigned char>& owner,
                       const unsigned char* first, const unsigned char* last) {
    owner.assign(first, last);
}

extern const unsigned long IntegralAssignmentLayout[] = {
    sizeof(int), sizeof(unsigned long), sizeof(unsigned char),
    sizeof(std::vector<unsigned long>), sizeof(std::deque<unsigned char>),
    sizeof(std::_Int_iterator_tag), sizeof(std::random_access_iterator_tag)
};
