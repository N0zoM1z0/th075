// The only reconstructed state here is the three original fighter notice
// bytes/shorts at their native locations; the whole Fighter is unknown.
class FighterNoticeF300 {public: void AdvanceNoticeLevels();public:
    // Observed fields; meanings not yet known.
    unsigned char unknown000[0x6E6 - 0x000];
    signed char field6E6;
    unsigned char unknown6E7[0x6EA - 0x6E7];
    short field6EA;
    short field6EC;
};
void FighterNoticeF300::AdvanceNoticeLevels()
{
    switch(field6E6) {
    case 0:
      if (field6EA<25)
        ++field6EA;
      break;
    case 1:
      if (field6EA>0)
        --field6EA;
      if (field6EC>0)
        --field6EC;
      break;
    case 2:
      if (field6EA>0)
        --field6EA;
      if (field6EC<5)
        ++field6EC;
      break;
    }
}
