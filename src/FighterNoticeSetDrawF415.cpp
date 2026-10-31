#include "FighterNoticeBorrowedF960.hpp"
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
class FighterNoticePairF414 {
public:
    void SetNoticeFields(signed char notice, unsigned char first, unsigned char second);
    void RenderNotice(void* text,unsigned char r,unsigned char g,unsigned char b,unsigned char highlighted);
};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
void FighterNoticePairF414::SetNoticeFields(signed char notice,unsigned char first,unsigned char second) {
    if(notice>=0 && notice<=FIELD(signed char,0x532))
        F960_BADGE(this).noticeAt6E7=notice;
    F960_BADGE(this).firstAt6E8=first;
    F960_BADGE(this).colorAt6E9=second;
}
void FighterNoticePairF414::RenderNotice(void* text,unsigned char r,unsigned char g,unsigned char b,unsigned char highlighted) {
    if(g_BattleCharacterNumberAt0067161E<8)
        g_NoticeRendererAt0067143C->DrawNotice(text,r,g,b,24,F960_STEP_LOW_BYTE(this),highlighted);
    else
        g_NoticeRendererAt0067143C->DrawNotice(text,r,g,b,16,F960_STEP_LOW_BYTE(this),highlighted);
}
#undef FIELD
