#include "replay/ReplaySegmentedQueueF219.hpp"

template<>
void ReplayRecords::ClearFourQueues()
{
    byteInputs.clear();
    wordInputs.clear();
    secondaryInputs.clear();
    dwordInputs.clear();
}

template<>
unsigned char ReplayRecords::IsPrimaryInputQueueEmpty()
{
    if (byteInputs.size() > 0)
        return 0;
    return 1;
}
