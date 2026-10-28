// Only the native-observed fighter notice-mode byte is exposed.
class FighterNoticeF283 {
public:
    void SetNoticeModeByte(unsigned char mode);
};
void FighterNoticeF283::SetNoticeModeByte(unsigned char mode)
{
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+0x6e4)=mode;
}
