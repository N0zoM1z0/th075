// Complete generic observations retain the old list model; no original sprite owner.
#include "VC7ListPolicyDependencies.cpp"
#include <queue>
struct GuardedSpriteListObservation : ListOwnerObservation {
    void removeFrontIfPresent();
};
void GuardedSpriteListObservation::removeFrontIfPresent() {
    if (entries.size() > 0) entries.pop_front();
}
typedef std::queue<ListValueObservation,std::list<ListValueObservation> > PublicListQueueObservation;
void ObservePublicQueuePop(PublicListQueueObservation& value) {
    value.pop();
}
void RemoveFrontFromBorrowedList(std::list<ListValueObservation>& entries) {
    if (entries.size() > 0) entries.pop_front();
}
extern const unsigned long GuardedSpriteListObservationSizes[] = {
    sizeof(ListValueObservation),sizeof(ListOwnerObservation),
    sizeof(GuardedSpriteListObservation),sizeof(PublicListQueueObservation)
};
