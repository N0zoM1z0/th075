// F805: original complete 00454C00 24-B unknown-origin native leaf.
// This C++ class is a BORROWED observed member-layout view ONLY.
// It is NOT the historical owner/name, nor proof of authored origin.
class BorrowedStateFlagF805 {
    unsigned char observedOnlyBefore47C[0x47C];
    unsigned int statusAt47C;
public:
    void ResetStatus();
};
void BorrowedStateFlagF805::ResetStatus() {
    statusAt47C = 0;
}
