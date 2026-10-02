#include <vector>

#define PROBE_RECORD(N)                                  \
    struct Rec##N { unsigned char data[N]; };            \
    extern std::vector<Rec##N> records##N;               \
    void ProbeRecord##N(unsigned int count, Rec##N value) \
    {                                                     \
        records##N.assign(count, value);                  \
    }

PROBE_RECORD(4)
PROBE_RECORD(8)
PROBE_RECORD(12)
PROBE_RECORD(20)
PROBE_RECORD(24)
PROBE_RECORD(28)
PROBE_RECORD(32)
PROBE_RECORD(40)
PROBE_RECORD(48)
PROBE_RECORD(64)
PROBE_RECORD(72)
PROBE_RECORD(80)
PROBE_RECORD(96)
PROBE_RECORD(128)
