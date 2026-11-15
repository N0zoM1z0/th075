#include "Fighter.hpp"
// The only reconstructed state here is the three original fighter notice
// bytes/shorts at their native locations; the whole Fighter is unknown.
void Fighter::AdvanceNoticeLevels()
{
    switch(noticeState) {
    case 0:
      if (noticeAxis<25)
        ++noticeAxis;
      break;
    case 1:
      if (noticeAxis>0)
        --noticeAxis;
      if (noticeExtent>0)
        --noticeExtent;
      break;
    case 2:
      if (noticeAxis>0)
        --noticeAxis;
      if (noticeExtent<5)
        ++noticeExtent;
      break;
    }
}
