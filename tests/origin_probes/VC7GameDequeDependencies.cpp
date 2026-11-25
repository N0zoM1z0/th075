// Independent source typing of the reviewed four-list traversal, not a
// recovered full game class layout or original element definition.
#include <deque>
struct EntryProbe {};
struct EffectListProbe {
    unsigned observed_leading_word;
    std::deque<EntryProbe*> lists[4];
    void DeleteEntries();
};
void EffectListProbe::DeleteEntries() {
    std::deque<EntryProbe*>::iterator current, last;
    for (int i = 0; i < 4; ++i) {
        current = lists[i].begin();
        last = lists[i].end();
        for (; current != last; current++) {
            if (*current) delete *current;
        }
        lists[i].clear();
    }
}

// Only the observed dispatch slot and member offset are modelled here.
struct AuxEntryProbe {
    virtual void UnknownSlot0();
    virtual void Advance();
    unsigned observed_field4;
    unsigned observed_field8;
};
struct AuxListProbe {
    std::deque<AuxEntryProbe*> lists[2];
    void AdvanceAndPrune();
};
void AuxListProbe::AdvanceAndPrune() {
    int i;
    for (i = 0; i < 2; ++i) {
        int count = lists[i].size();
        for (int j = 0; j < count; ++j) lists[i].at(j)->Advance();
        std::deque<AuxEntryProbe*>::iterator current = lists[i].begin();
        while (current != lists[i].end()) {
            if ((*current)->observed_field8 == 0) {
                delete *current;
                current = lists[i].erase(current);
            } else current++;
        }
    }
}
