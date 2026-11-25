#include "battle/BattleSessionState.hpp"
#include "audio/AudioControl.hpp"
#include "battle/Fighter.hpp"
// Independently verified complete R065-authored 1,926-byte fighter-script
// action dispatcher. The original 36-byte native jump table plus 15-byte
// 0..14 case remap DATA is compared but earns no executable CODE credit.
// The actual three used signed one-byte mask/bit/count locals precede
// all five compiler-generated meaningful unsigned-char notice Boolean
// temporaries. Genuine C++ casts directly at render call sites recover
// their native stack allocations after saved this and script-kind.
// The full mode, notice, stage-change, event-bit, and original active-input
// behavior was independently decoded before comparison.
signed char g_ActionLastIndexAt0066C24F = -1;
signed char g_ActionLastBitAt0066C24E = -1;
unsigned char Fighter::ProcessAction() {
  signed char mask,number,bit;
  if(scriptIndex>=script.CountCommands(scriptId) || scriptIndex<0) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
  }
  if(g_ActionLastIndexAt0066C24F!=scriptIndex || g_ActionLastBitAt0066C24E!=scriptStep) {
    switch(script.GetCommand(scriptId,scriptIndex)) {
      case StoryCommand::PlayerLine:
        if(script.GetArgument(scriptId,scriptIndex)<0) {
          ClearNoticeTransition();
          RenderNotice(script.GetDialogueText(scriptId,scriptIndex),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        } else {
          noticeState=1;
          SetNoticeFields(script.GetArgument(scriptId,scriptIndex),1,255);
          RenderNotice(script.GetDialogueText(scriptId,scriptIndex),120,120,255,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
          if(opponent->noticeState>0) {
            opponent->noticeState=2;
            static_cast<Fighter*>(opponent)->SetNoticeFields(-1,0,128);
          }
        }
        break;
      case StoryCommand::OpponentLine:
        if(script.GetArgument(scriptId,scriptIndex)<0) {
          static_cast<Fighter*>(opponent)->ClearNoticeTransition();
          RenderNotice(script.GetDialogueText(scriptId,scriptIndex),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        } else {
          opponent->noticeState=1;
          static_cast<Fighter*>(opponent)->SetNoticeFields(script.GetArgument(scriptId,scriptIndex),1,255);
          RenderNotice(script.GetDialogueText(scriptId,scriptIndex),255,120,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
          if(noticeState>0) {
            noticeState=2;
            SetNoticeFields(-1,0,128);
          }
        }
        break;
      case StoryCommand::NarrationLine: {
          RenderNotice(script.GetDialogueText(scriptId,scriptIndex),120,255,120,static_cast<unsigned char>((g_ActionLastBitAt0066C24E!=scriptStep && g_ActionLastIndexAt0066C24F==scriptIndex)));
        }break;
      case StoryCommand::SetStageBanner: stageBannerEnabled=static_cast<unsigned char>(script.GetArgument(scriptId,scriptIndex));break;
      case StoryCommand::PlayTrack:
          MusicF204::PlayTrackByIndex(script.GetArgument(scriptId,scriptIndex));
          MusicF205::ScheduleTransitionFade();
          break;
      case StoryCommand::SetQueuedMusicDelay: queuedMusicDelayFrames=script.GetArgument(scriptId,scriptIndex);break;
      case StoryCommand::SetQueuedMusicTrack: queuedMusicTrack=script.GetArgument(scriptId,scriptIndex);break;
      case StoryCommand::SetDialogueSteps: {
          scriptBitMask=script.GetArgument(scriptId,scriptIndex);
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
  if(script.GetCommand(scriptId,scriptIndex)>=StoryCommand::SetStageBanner) {
    ++scriptIndex;
    if(scriptIndex==script.CountCommands(scriptId)) {
      g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
    }
  } else if (field4E4==1 || g_InputCanCancelAt00671632) {
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
      if(scriptIndex==script.CountCommands(scriptId)) {
        g_ActionLastIndexAt0066C24F=-1;g_ActionLastBitAt0066C24E=-1;return 1;
      }
    }
  }
  return 0;
}
