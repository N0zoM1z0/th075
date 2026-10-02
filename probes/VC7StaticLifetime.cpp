#include "InputDevice.hpp"
#include <string>
#include <vector>

std::string probe_global_string;
std::vector<unsigned int> probe_global_numbers;
std::string probe_global_strings[2];

struct ProbeNoDestructor {
    ProbeNoDestructor() : value(1) {}
    unsigned int value;
};
ProbeNoDestructor probe_global_counter;
