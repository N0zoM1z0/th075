// The only reconstructed state here is the three original fighter notice
// bytes/shorts at their native locations; the whole FighterState is unknown.
class FighterNoticeF300 {public: void AdvanceNoticeLevels();};
#define FIELD(type,offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
void FighterNoticeF300::AdvanceNoticeLevels()
{
    switch(FIELD(signed char,0x6e6)) {
    case 0:
      if (FIELD(short,0x6ea)<25)
        ++FIELD(short,0x6ea);
      break;
    case 1:
      if (FIELD(short,0x6ea)>0)
        --FIELD(short,0x6ea);
      if (FIELD(short,0x6ec)>0)
        --FIELD(short,0x6ec);
      break;
    case 2:
      if (FIELD(short,0x6ea)>0)
        --FIELD(short,0x6ea);
      if (FIELD(short,0x6ec)<5)
        ++FIELD(short,0x6ec);
      break;
    }
}
#undef FIELD
