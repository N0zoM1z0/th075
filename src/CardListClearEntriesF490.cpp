#include "ResultListScene.hpp"

void ResultListScene::ClearEntries()
{
    for (unsigned int index = 0; index < records.size(); ++index) {
        if (records[index])
            delete[] records[index];
    }
    records.clear();
}
