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

  unsigned char unknown000[0x2E8];
  FighterActionF410* opponent;              // +0x2E8
  unsigned char unknown2EC[0x4E4 - 0x2EC];
  int inputMode;                            // +0x4E4
  unsigned char unknown4E8[0x6E6 - 0x4E8];
  signed char noticeState;                  // +0x6E6
  unsigned char unknown6E7[0x6F0 - 0x6E7];
  short scriptId;                           // +0x6F0
  short scriptBitMask;                      // +0x6F2
  short scriptIndex;                        // +0x6F4
  short scriptStep;                         // +0x6F6
  unsigned char scriptByte6F8;              // +0x6F8
  unsigned char unknown6F9;
  short scriptWord6FA;                      // +0x6FA
  short scriptWord6FC;                      // +0x6FC
  unsigned char unknown6FE[0x714 - 0x6FE];
  FighterScriptAccessorF410 script;         // +0x714
};
extern signed char g_ActionLastIndexAt0066C24F;
extern signed char g_ActionLastBitAt0066C24E;
extern unsigned char g_InputCanCancelAt00671632;
extern void SelectStageAt00419CB0(int);
extern void RebuildStageAt00419DF0();
unsigned char FighterActionF410::ProcessAction() {
  signed char mask,number,bit;
  if(scriptIndex>=script.CountPatternEntries(scriptId) || scriptIndex<0) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
  }
  if(g_ActionLastIndexAt0066C24F!=scriptIndex || g_ActionLastBitAt0066C24E!=scriptStep) {
    switch(script.GetByteField(scriptId,scriptIndex)) {
      case 0:
        if(script.GetWordField(scriptId,scriptIndex)<0) {
          ClearNoticeTransition();
          RenderNotice(script.GetDwordField(scriptId,scriptIndex),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        } else {
          noticeState=1;
          SetNoticeFields(script.GetWordField(scriptId,scriptIndex),1,255);
          RenderNotice(script.GetDwordField(scriptId,scriptIndex),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
          if(opponent->noticeState>0) {
            opponent->noticeState=2;
            opponent->SetNoticeFields(-1,0,128);
          }
        }
        break;
      case 1:
        if(script.GetWordField(scriptId,scriptIndex)<0) {
          opponent->ClearNoticeTransition();
          RenderNotice(script.GetDwordField(scriptId,scriptIndex),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        } else {
          opponent->noticeState=1;
          opponent->SetNoticeFields(script.GetWordField(scriptId,scriptIndex),1,255);
          RenderNotice(script.GetDwordField(scriptId,scriptIndex),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
          if(noticeState>0) {
            noticeState=2;
            SetNoticeFields(-1,0,128);
          }
        }
        break;
      case 2: {
          RenderNotice(script.GetDwordField(scriptId,scriptIndex),120,255,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        }break;
      case 10: scriptByte6F8=static_cast<unsigned char>(script.GetWordField(scriptId,scriptIndex));break;
      case 11:
          SelectStageAt00419CB0(script.GetWordField(scriptId,scriptIndex));
          RebuildStageAt00419DF0();
          break;
      case 12: scriptWord6FA=script.GetWordField(scriptId,scriptIndex);break;
      case 13: scriptWord6FC=script.GetWordField(scriptId,scriptIndex);break;
      case 14: {
          scriptBitMask=script.GetWordField(scriptId,scriptIndex);
          if(scriptBitMask>0) {
              scriptStep=1;
              mask=1;
              while(!(scriptBitMask & mask)) { ++scriptStep; mask<<=1; }
              scriptBitMask-=mask;
          } else scriptStep=5;
        }break;
      }
    g_ActionLastIndexAt0066C24F=static_cast<signed char>(scriptIndex);
    g_ActionLastBitAt0066C24E=static_cast<signed char>(scriptStep);
  }
  if(script.GetByteField(scriptId,scriptIndex)>=10) {
    ++scriptIndex;
    if(scriptIndex==script.CountPatternEntries(scriptId)) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
    }
  } else if (inputMode==1 || g_InputCanCancelAt00671632) {
    if(scriptBitMask>0) {
      bit=1;
      number=1;
      while(!(scriptBitMask & bit)) { ++number; bit<<=1; }
      scriptStep=number;
      scriptBitMask-=bit;
      if(scriptBitMask==0) scriptStep=5;
    } else {
      scriptStep=5;
      ++scriptIndex;
      if(scriptIndex==script.CountPatternEntries(scriptId)) {
        g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
      }
    }
  }
  return 0;
}
