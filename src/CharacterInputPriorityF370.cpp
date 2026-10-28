// Complete borrowed 27-pattern command-priority input controller. Each
// genuine pattern has its own original constant pool address. The receiver
// class and command string contents are not asserted beyond these reads.
class CharacterInputPriorityF370 { public:
  void ResolvePriority();
  signed char CheckPattern(const char*, int, int);
};
extern const char g_ComboPatternAt00659920[];
extern const char g_ComboPatternAt00659928[];
extern const char g_ComboPatternAt00659930[];
extern const char g_ComboPatternAt00659938[];
extern const char g_ComboPatternAt00659940[];
extern const char g_ComboPatternAt00659948[];
extern const char g_ComboPatternAt00659950[];
extern const char g_ComboPatternAt00659958[];
extern const char g_ComboPatternAt00659960[];
extern const char g_ComboPatternAt00659968[];
extern const char g_ComboPatternAt00659970[];
extern const char g_ComboPatternAt00659978[];
extern const char g_ComboPatternAt00659980[];
extern const char g_ComboPatternAt00659988[];
extern const char g_ComboPatternAt00659990[];
extern const char g_ComboPatternAt00659998[];
extern const char g_ComboPatternAt006599A0[];
extern const char g_ComboPatternAt006599A4[];
extern const char g_ComboPatternAt006599A8[];
extern const char g_ComboPatternAt006599AC[];
extern const char g_ComboPatternAt006599B0[];
extern const char g_ComboPatternAt006599B4[];
extern const char g_ComboPatternAt006599B8[];
extern const char g_ComboPatternAt006599BC[];
extern const char g_ComboPatternAt006599C0[];
extern const char g_ComboPatternAt006599C4[];
extern const char g_ComboPatternAt006599CC[];
#define STATUS (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+0x511))
void CharacterInputPriorityF370::ResolvePriority() {
    STATUS = 0;
    if (CheckPattern(g_ComboPatternAt00659920,5,15)) STATUS=61;
    else if (CheckPattern(g_ComboPatternAt00659928,5,15)) STATUS=60;
    else if (CheckPattern(g_ComboPatternAt00659930,5,15)) STATUS=51;
    else if (CheckPattern(g_ComboPatternAt00659938,5,15)) STATUS=50;
    else if (CheckPattern(g_ComboPatternAt00659940,4,15)) STATUS=31;
    else if (CheckPattern(g_ComboPatternAt00659948,4,15)) STATUS=30;
    else if (CheckPattern(g_ComboPatternAt00659950,4,15)) STATUS=21;
    else if (CheckPattern(g_ComboPatternAt00659958,4,15)) STATUS=20;
    else if (CheckPattern(g_ComboPatternAt00659960,4,15)) STATUS=13;
    else if (CheckPattern(g_ComboPatternAt00659968,4,15)) STATUS=12;
    else if (CheckPattern(g_ComboPatternAt00659970,4,15)) STATUS=11;
    else if (CheckPattern(g_ComboPatternAt00659978,4,15)) STATUS=10;
    else if (CheckPattern(g_ComboPatternAt00659980,4,15)) STATUS=103;
    else if (CheckPattern(g_ComboPatternAt00659988,4,15)) STATUS=102;
    else if (CheckPattern(g_ComboPatternAt00659990,4,15)) STATUS=101;
    else if (CheckPattern(g_ComboPatternAt00659998,4,15)) STATUS=100;
    else if (CheckPattern(g_ComboPatternAt006599A0,3,10)) STATUS=5;
    else if (CheckPattern(g_ComboPatternAt006599A4,3,10)) STATUS=5;
    else if (CheckPattern(g_ComboPatternAt006599A8,3,10)) STATUS=5;
    else if (CheckPattern(g_ComboPatternAt006599AC,3,10)) STATUS=4;
    else if (CheckPattern(g_ComboPatternAt006599B0,3,10)) STATUS=4;
    else if (CheckPattern(g_ComboPatternAt006599B4,3,10)) STATUS=4;
    else if (CheckPattern(g_ComboPatternAt006599B8,3,10)) STATUS=3;
    else if (CheckPattern(g_ComboPatternAt006599BC,3,10)) STATUS=3;
    else if (CheckPattern(g_ComboPatternAt006599C0,3,10)) STATUS=3;
    else if (CheckPattern(g_ComboPatternAt006599C4,4,15)) STATUS=1;
    else if (CheckPattern(g_ComboPatternAt006599CC,4,15)) STATUS=2;
}
#undef STATUS
