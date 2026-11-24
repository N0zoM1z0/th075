#include "TextOverlay.hpp"
#include "Fighter.hpp"
// Two complete original fighter notice policies. Actual index guard only
// controls the first notice byte: subsequent state/color byte writes
// must happen even when notice index is invalid. The rendering backend
// takes real unsigned byte arguments, not int-promoted surrogates.
// Two physically complete native fighter notice policies; only borrowed
// owner offsets and the original notice-drawing renderer ABI are asserted.
extern signed char g_BattleCharacterNumberAt0067161E;
void Fighter::SetNoticeFields(signed char notice,unsigned char first,unsigned char second) {
    if(notice>=0 && notice<=field532)
        noticeBadge=notice;
    noticeFirst=first;
    noticeColor=second;
}
void Fighter::RenderNotice(void* text,unsigned char r,unsigned char g,unsigned char b,unsigned char highlighted) {
    if(g_BattleCharacterNumberAt0067161E<8)
        g_TextRenderer->RenderTextToTexture(static_cast<const char*>(text),r,g,b,24,scriptStep,highlighted);
    else
        g_TextRenderer->RenderTextToTexture(static_cast<const char*>(text),r,g,b,16,scriptStep,highlighted);
}
