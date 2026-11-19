#include "ReplaySegmentedQueueF219.hpp"

// Queue method facades share the concrete segmented storage layout. Their
// element-operation bodies remain separate native helpers.
class ByteQueueF220 : public ReplaySegmentedQueueStorageF219<char> {
public: void Clear(); unsigned int Size();
};
class WordQueueF220 : public ReplaySegmentedQueueStorageF219<short> {
public: void Clear();
};
class DwordQueueF220 : public ReplaySegmentedQueueStorageF219<unsigned int> {
public: void Clear();
};
typedef ReplayRecordsLayoutF219<ByteQueueF220,WordQueueF220,DwordQueueF220> ReplayQueuePolicyLayoutF220;
class ReplayQueuePolicyF220 : public ReplayQueuePolicyLayoutF220 {
public:
    void ClearFourQueues();
    unsigned char IsPrimaryInputQueueEmpty();
};
void ReplayQueuePolicyF220::ClearFourQueues()
{
    byteInputs.Clear();
    wordInputs.Clear();
    secondaryInputs.Clear();
    dwordInputs.Clear();
}
unsigned char ReplayQueuePolicyF220::IsPrimaryInputQueueEmpty()
{
    if (byteInputs.Size()>0)
        return 0;
    return 1;
}
