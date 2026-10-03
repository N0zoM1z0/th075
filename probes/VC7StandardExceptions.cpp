// Independent VC7.1 standard exception emission, including implicit copies.
// Type descriptors distinguish sibling classes with identical method shapes.
#include <stdexcept>
#include <string>

#define PROBE_EXCEPTION(T, N) \
  void ProbeException##N(const std::string& message) { \
    std::T original(message); \
    std::T copy(original); \
    throw copy; \
  }

PROBE_EXCEPTION(domain_error, Domain)
PROBE_EXCEPTION(invalid_argument, InvalidArgument)
PROBE_EXCEPTION(length_error, Length)
PROBE_EXCEPTION(out_of_range, OutOfRange)
PROBE_EXCEPTION(range_error, Range)
PROBE_EXCEPTION(overflow_error, Overflow)
PROBE_EXCEPTION(underflow_error, Underflow)
