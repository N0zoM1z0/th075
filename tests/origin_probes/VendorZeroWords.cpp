// Complete ordinary zeroing controls; no original PNG or floating type is declared.
#include <string.h>
struct SixteenWordStorage { unsigned long words[16]; };
struct ThreeWordStorage { unsigned long words[3]; };
void ClearSixteenWords(SixteenWordStorage *storage)
{
    memset(storage, 0, sizeof(*storage));
}
void ClearThreeWords(ThreeWordStorage *storage)
{
    memset(storage, 0, sizeof(*storage));
}
extern const unsigned long ZeroWordControlSizes[] = {
    sizeof(SixteenWordStorage), sizeof(ThreeWordStorage), sizeof(unsigned long)
};
