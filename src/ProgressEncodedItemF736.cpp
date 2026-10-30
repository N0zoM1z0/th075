// F736: R021 authored signed-byte decimal group rule and record access.
// Exact native IDIV signed remainder and real 006718F8 record method;
// original record class name/layout remains provisional.
class GameProgressCatalogF736 {
public: bool CheckEncodedSlot(int index);
};
extern GameProgressCatalogF736 g_GameProgressCatalogAt006718F8;
namespace ProgressRecordsF736 {
    bool CheckEncodedItem(signed char code);
}
bool ProgressRecordsF736::CheckEncodedItem(signed char code) {
    if (code % 10 < 6) return true;
    return g_GameProgressCatalogAt006718F8.CheckEncodedSlot(
        static_cast<int>(code) + 200);
}
