// Independent VC7.1 vector operation probe.
// Widths and scalar variants test template emission, not original game types.
#include <vector>

template<unsigned N> struct VectorOperationRecord { unsigned char bytes[N]; };

#define PROBE_VECTOR(T, N) \
  typedef T VectorOperationValue##N; \
  std::vector<VectorOperationValue##N > operation_vector_##N; \
  void ProbeVector##N(unsigned count, const VectorOperationValue##N& value) { \
    operation_vector_##N.assign(count, value); \
    operation_vector_##N.insert(operation_vector_##N.begin(), count, value); \
    operation_vector_##N.erase(operation_vector_##N.begin(), operation_vector_##N.end()); \
    operation_vector_##N.clear(); \
    operation_vector_##N.reserve(count); \
    operation_vector_##N.resize(count, value); \
    operation_vector_##N.push_back(value); \
    operation_vector_##N.pop_back(); \
  }

PROBE_VECTOR(VectorOperationRecord<1>, 1)
PROBE_VECTOR(VectorOperationRecord<2>, 2)
PROBE_VECTOR(VectorOperationRecord<4>, 4)
PROBE_VECTOR(VectorOperationRecord<8>, 8)
PROBE_VECTOR(VectorOperationRecord<16>, 16)
PROBE_VECTOR(VectorOperationRecord<32>, 32)
PROBE_VECTOR(VectorOperationRecord<44>, 44)
PROBE_VECTOR(VectorOperationRecord<64>, 64)
PROBE_VECTOR(VectorOperationRecord<80>, 80)
PROBE_VECTOR(VectorOperationRecord<116>, 116)
PROBE_VECTOR(unsigned char, Byte)
PROBE_VECTOR(unsigned short, Word)
PROBE_VECTOR(unsigned long, Dword)
PROBE_VECTOR(float, Float)
PROBE_VECTOR(double, Double)
PROBE_VECTOR(void*, Pointer)
