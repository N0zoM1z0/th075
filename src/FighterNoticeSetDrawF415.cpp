#include "Fighter.hpp"
// Two complete original fighter notice policies. Actual index guard only
// controls the first notice byte: subsequent state/color byte writes
// must happen even when notice index is invalid. The rendering backend
// takes real unsigned byte arguments, not int-promoted surrogates.
// Two physically complete native fighter notice policies; only borrowed
// owner offsets and the original notice-drawing renderer ABI are asserted.
class NoticeDrawingF414 {
public:
    void DrawNotice(void* text,unsigned char r,unsigned char g,unsigned char b,int depth,unsigned char step,unsigned char highlighted);
};
extern signed char g_BattleCharacterNumberAt0067161E;
extern NoticeDrawingF414* g_NoticeRendererAt0067143C;
void Fighter::SetNoticeFields(signed char notice,unsigned char first,unsigned char second) {
    if(notice>=0 && notice<=field532)
        noticeBadge=notice;
    noticeFirst=first;
    noticeColor=second;
}
void Fighter::RenderNotice(void* text,unsigned char r,unsigned char g,unsigned char b,unsigned char highlighted) {
    if(g_BattleCharacterNumberAt0067161E<8)
        g_NoticeRendererAt0067143C->DrawNotice(text,r,g,b,24,reinterpret_cast<unsigned char&>(scriptStep),highlighted);
    else
        g_NoticeRendererAt0067143C->DrawNotice(text,r,g,b,16,reinterpret_cast<unsigned char&>(scriptStep),highlighted);
}
