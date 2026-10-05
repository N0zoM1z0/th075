// Original public indexing source; generic carriers do not recover private types.
#include "VectorAtPolicyProbe.cpp"

extern const unsigned long FrameIndexPolicyLayout[] = {
    sizeof(AtValue4), sizeof(AtValue16), sizeof(std::vector<AtValue4>),
    sizeof(std::vector<AtValue16>), sizeof(std::vector<AtValue4>::iterator)
};
