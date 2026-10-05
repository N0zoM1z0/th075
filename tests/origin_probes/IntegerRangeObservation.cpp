// Generic arithmetic observations, not declarations of private game owners.
#include <algorithm>
#include <cstdlib>

class IntegerRangeObservation {
public:
    int Range(int lower, int upper);
    int ModuloRange(int lower, int upper);
};

int IntegerRangeObservation::Range(int lower, int upper) {
    return lower + rand() * (upper - lower) / (RAND_MAX + 1);
}

int IntegerRangeObservation::ModuloRange(int lower, int upper) {
    return lower + rand() % (upper - lower);
}

class GenericDistributionObservation {
public:
    int Range(int lower, int upper);
};

int GenericDistributionObservation::Range(int lower, int upper) {
    return lower + rand() * (upper - lower) / (RAND_MAX + 1);
}

extern "C" void OriginalSdkRandomShuffle(unsigned long* first, unsigned long* last) {
    std::random_shuffle(first, last);
}

extern const unsigned long IntegerRangeLayout[] = {
    sizeof(IntegerRangeObservation), sizeof(GenericDistributionObservation),
    sizeof(int), RAND_MAX
};
