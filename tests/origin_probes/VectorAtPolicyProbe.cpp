// Complete original public templates; element shapes are generic alternatives.
// No private game element type or incomplete owner is declared or instantiated.
#include <vector>
#include <stddef.h>

struct AtValue4 { unsigned long values[1]; };
struct AtValue8 { unsigned long values[2]; };
struct AtValue16 { unsigned long values[4]; };
struct AtValue116 { unsigned long values[29]; };

AtValue4 &ProbeAt4(std::vector<AtValue4> *owner, unsigned int index)
{
    return owner->at(index);
}

const AtValue4 &ProbeConstAt4(const std::vector<AtValue4> *owner, unsigned int index)
{
    return owner->at(index);
}

AtValue8 &ProbeAt8(std::vector<AtValue8> *owner, unsigned int index)
{
    return owner->at(index);
}

const AtValue8 &ProbeConstAt8(const std::vector<AtValue8> *owner, unsigned int index)
{
    return owner->at(index);
}

AtValue16 &ProbeAt16(std::vector<AtValue16> *owner, unsigned int index)
{
    return owner->at(index);
}

const AtValue16 &ProbeConstAt16(const std::vector<AtValue16> *owner, unsigned int index)
{
    return owner->at(index);
}

AtValue116 &ProbeAt116(std::vector<AtValue116> *owner, unsigned int index)
{
    return owner->at(index);
}

const AtValue116 &ProbeConstAt116(const std::vector<AtValue116> *owner, unsigned int index)
{
    return owner->at(index);
}

extern const unsigned int VectorAtPublicLayout[] = {
    sizeof(void *), sizeof(unsigned int), sizeof(AtValue4), sizeof(AtValue8), sizeof(AtValue16), sizeof(AtValue116),
    sizeof(std::vector<AtValue4>), sizeof(std::vector<AtValue4>::iterator),
    sizeof(std::vector<AtValue4>::const_iterator)
};
