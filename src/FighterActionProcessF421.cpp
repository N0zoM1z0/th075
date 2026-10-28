// Independently verified complete R065-authored 1,926-byte fighter-script
// action dispatcher. The original 36-byte native jump table plus 15-byte
// 0..14 case remap DATA is compared but earns no executable CODE credit.
// The actual three used signed one-byte mask/bit/count locals precede
// all five compiler-generated meaningful unsigned-char notice Boolean
// temporaries. Genuine C++ casts directly at render call sites recover
// their native stack allocations after saved this and script-kind.
// The full mode, notice, stage-change, event-bit, and original active-input
// behavior was independently decoded before comparison.
// Only native observed script reader, opponent and effect ABI; no full owner.
class FighterScriptAccessorF410 {public:
  short CountPatternEntries(short script);
  signed char GetByteField(short script,short index);
  short GetWordField(short script,short index);
  void* GetDwordField(short script,short index);
};
class FighterActionF410 {public:
  unsigned char ProcessAction();
  void ClearNoticeTransition();
  void SetNoticeFields(signed char value,unsigned char enabled,unsigned char alpha);
  void RenderNotice(void* text,unsigned char red,unsigned char green,unsigned char blue,unsigned char highlighted);
};
extern signed char g_ActionLastIndexAt0066C24F;
extern signed char g_ActionLastBitAt0066C24E;
extern unsigned char g_InputCanCancelAt00671632;
extern void SelectStageAt00419CB0(int);
extern void RebuildStageAt00419DF0();
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
#define SCRIPT (*reinterpret_cast<FighterScriptAccessorF410*>(reinterpret_cast<unsigned char*>(this)+0x714))
#define OPPONENT (*reinterpret_cast<FighterActionF410*>(FIELD(void*,0x2E8)))
#define OPPFIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x2E8))+(o)))
#define SCRIPTID FIELD(short,0x6F0)
#define SCRIPTINDEX FIELD(short,0x6F4)
#define SCRIPTSTEP FIELD(short,0x6F6)
#define BITMASK FIELD(short,0x6F2)
unsigned char FighterActionF410::ProcessAction() {
  signed char mask,number,bit;
  if(SCRIPTINDEX>=SCRIPT.CountPatternEntries(SCRIPTID) || SCRIPTINDEX<0) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
  }
  if(g_ActionLastIndexAt0066C24F!=SCRIPTINDEX || g_ActionLastBitAt0066C24E!=SCRIPTSTEP) {
    switch(SCRIPT.GetByteField(SCRIPTID,SCRIPTINDEX)) {
      case 0:
        if(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX)<0) {
          ClearNoticeTransition();
          RenderNotice(SCRIPT.GetDwordField(SCRIPTID,SCRIPTINDEX),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=SCRIPTSTEP && g_ActionLastIndexAt0066C24F==SCRIPTINDEX)));
        } else {
          FIELD(unsigned char,0x6E6)=1;
          SetNoticeFields(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX),1,255);
          RenderNotice(SCRIPT.GetDwordField(SCRIPTID,SCRIPTINDEX),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=SCRIPTSTEP && g_ActionLastIndexAt0066C24F==SCRIPTINDEX)));
          if(OPPFIELD(signed char,0x6E6)>0) {
            OPPFIELD(unsigned char,0x6E6)=2;
            OPPONENT.SetNoticeFields(-1,0,128);
          }
        }
        break;
      case 1:
        if(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX)<0) {
          OPPONENT.ClearNoticeTransition();
          RenderNotice(SCRIPT.GetDwordField(SCRIPTID,SCRIPTINDEX),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=SCRIPTSTEP && g_ActionLastIndexAt0066C24F==SCRIPTINDEX)));
        } else {
          OPPFIELD(unsigned char,0x6E6)=1;
          OPPONENT.SetNoticeFields(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX),1,255);
          RenderNotice(SCRIPT.GetDwordField(SCRIPTID,SCRIPTINDEX),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=SCRIPTSTEP && g_ActionLastIndexAt0066C24F==SCRIPTINDEX)));
          if(FIELD(signed char,0x6E6)>0) {
            FIELD(unsigned char,0x6E6)=2;
            SetNoticeFields(-1,0,128);
          }
        }
        break;
      case 2: {
          RenderNotice(SCRIPT.GetDwordField(SCRIPTID,SCRIPTINDEX),120,255,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=SCRIPTSTEP && g_ActionLastIndexAt0066C24F==SCRIPTINDEX)));
        }break;
      case 10: FIELD(unsigned char,0x6F8)=static_cast<unsigned char>(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX));break;
      case 11:
          SelectStageAt00419CB0(SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX));
          RebuildStageAt00419DF0();
          break;
      case 12: FIELD(short,0x6FA)=SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX);break;
      case 13: FIELD(short,0x6FC)=SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX);break;
      case 14: {
          BITMASK=SCRIPT.GetWordField(SCRIPTID,SCRIPTINDEX);
          if(BITMASK>0) {
              SCRIPTSTEP=1;
              mask=1;
              while(!(BITMASK & mask)) { ++SCRIPTSTEP; mask<<=1; }
              BITMASK-=mask;
          } else SCRIPTSTEP=5;
        }break;
      }
    g_ActionLastIndexAt0066C24F=static_cast<signed char>(SCRIPTINDEX);
    g_ActionLastBitAt0066C24E=static_cast<signed char>(SCRIPTSTEP);
  }
  if(SCRIPT.GetByteField(SCRIPTID,SCRIPTINDEX)>=10) {
    ++SCRIPTINDEX;
    if(SCRIPTINDEX==SCRIPT.CountPatternEntries(SCRIPTID)) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
    }
  } else if (FIELD(int,0x4E4)==1 || g_InputCanCancelAt00671632) {
    if(BITMASK>0) {
      bit=1;
      number=1;
      while(!(BITMASK & bit)) { ++number; bit<<=1; }
      SCRIPTSTEP=number;
      BITMASK-=bit;
      if(BITMASK==0) SCRIPTSTEP=5;
    } else {
      SCRIPTSTEP=5;
      ++SCRIPTINDEX;
      if(SCRIPTINDEX==SCRIPT.CountPatternEntries(SCRIPTID)) {
        g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
      }
    }
  }
  return 0;
}
#undef BITMASK
#undef SCRIPTSTEP
#undef SCRIPTINDEX
#undef SCRIPTID
#undef OPPFIELD
#undef OPPONENT
#undef SCRIPT
#undef FIELD
