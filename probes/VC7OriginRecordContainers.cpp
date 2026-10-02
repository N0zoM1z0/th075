#include <vector>

struct Record16 { unsigned char data[16]; };
struct Record44 { unsigned char data[44]; };
struct Record116 { unsigned char data[116]; };

extern std::vector<Record16> records16;
extern std::vector<Record44> records44;
extern std::vector<Record116> records116;

void ProbeRecord16(unsigned int count, Record16 value)
{
    records16.assign(count, value);
}

void ProbeRecord44(unsigned int count, Record44 value)
{
    records44.assign(count, value);
}

void ProbeRecord116(unsigned int count, Record116 value)
{
    records116.assign(count, value);
}
