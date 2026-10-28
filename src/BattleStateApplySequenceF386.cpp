// Complete original R065 1,958-CODE-byte battle input/replay dispatcher.
// The separately owned 28-byte native 7-entry switch table is validated in
// compare_size=1986 but earns zero additional authored CODE credit.
// Actual source-side unsigned Count()>0 and <=0, real thiscall key scanner,
// and positive cancel-flag condition preserve native original branch layout.
// firstRecord is physically read and stored in the original even though
// another Peek() reads the active command before dispatch.
// Observed original call ABIs and field offsets only, not a whole battle class.
class ReplayQueueF385 {
public:
    unsigned int Count();
    int* Peek();
    void Pop();
    void Append(const int* item);
};
extern ReplayQueueF385 g_ReplayEventsAt006718E0;
extern signed char g_BattleModeAt006714B4;
extern signed char g_ReplayModeAt0066C238;
extern signed char g_StageIdAt0067161D;
extern unsigned int g_InputGateAt00671678;
extern unsigned char g_InputCanCancelAt00671632;
extern const float g_LevelStepAt00657850;
extern const float g_LevelMaxAt00657B28;
extern const float g_LevelZeroAt0065782C;
class NativeKeyScannerF386 {public: unsigned char CheckKey(int);};
extern NativeKeyScannerF386 g_KeyScannerAt00671638;
extern void NativeActionAt00423C60(int);
class BattleStateF385 {public:
    void ApplySequence();
    void OnCameraModeFive();
};
#define FIELD(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(this)+(o)))
#define LEFT(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x44))+(o)))
#define RIGHT(T,o) (*reinterpret_cast<T*>(reinterpret_cast<unsigned char*>(FIELD(void*,0x48))+(o)))
void BattleStateF385::ApplySequence() {
    if(g_BattleModeAt006714B4==5) {
        OnCameraModeFive();
    } else {
        if(g_ReplayModeAt0066C238==2) {
            if(g_ReplayEventsAt006718E0.Count()>0) {
                int firstRecord=*g_ReplayEventsAt006718E0.Peek();
                while(FIELD(int,0x14)==*g_ReplayEventsAt006718E0.Peek()) {
                    g_ReplayEventsAt006718E0.Pop();
                    int command=*g_ReplayEventsAt006718E0.Peek();
                    g_ReplayEventsAt006718E0.Pop();
                    switch(command) {
                    case 1: RIGHT(short,0x324)=1;break;
                    case 2: LEFT(signed char,0x39D)=2;RIGHT(signed char,0x39D)=2;break;
                    case 3:
                        if(LEFT(signed char,0x39D)>1) --LEFT(signed char,0x39D);
                        if(RIGHT(signed char,0x39D)>1) --RIGHT(signed char,0x39D);
                        break;
                    case 4: FIELD(unsigned char,0x1C)=0;break;
                    case 5: FIELD(unsigned char,0x1C)=1;break;
                    case 6:
                        LEFT(float,0x36C)=LEFT(float,0x36C)+g_LevelStepAt00657850;
                        RIGHT(float,0x36C)=RIGHT(float,0x36C)+g_LevelStepAt00657850;
                        if(LEFT(float,0x36C)>g_LevelMaxAt00657B28) LEFT(float,0x36C)=900.0f;
                        if(RIGHT(float,0x36C)>g_LevelMaxAt00657B28) RIGHT(float,0x36C)=900.0f;
                        break;
                    case 7:
                        LEFT(float,0x36C)=LEFT(float,0x36C)-g_LevelStepAt00657850;
                        RIGHT(float,0x36C)=RIGHT(float,0x36C)-g_LevelStepAt00657850;
                        if(LEFT(float,0x36C)<g_LevelZeroAt0065782C) LEFT(float,0x36C)=0.0f;
                        if(RIGHT(float,0x36C)<g_LevelZeroAt0065782C) RIGHT(float,0x36C)=0.0f;
                        break;
                    }
                    if(g_ReplayEventsAt006718E0.Count()<=0) break;
                }
            }
        } else {
            if(!g_KeyScannerAt00671638.CheckKey(0x3D)) FIELD(int,0x110)=0;
            if(g_BattleModeAt006714B4!=3 && g_BattleModeAt006714B4!=4) {
                if(g_KeyScannerAt00671638.CheckKey(0x3C)) {
                    if(g_ReplayModeAt0066C238==1) {
                        g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                        int action2=2;g_ReplayEventsAt006718E0.Append(&action2);
                    }
                    LEFT(signed char,0x39D)=2;RIGHT(signed char,0x39D)=2;
                }
                if(g_KeyScannerAt00671638.CheckKey(0x3D)) {
                    if(FIELD(int,0x110)==0) {
                        if(g_ReplayModeAt0066C238==1) {
                            g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                            int action3=3;g_ReplayEventsAt006718E0.Append(&action3);
                        }
                        if(LEFT(signed char,0x39D)>1) --LEFT(signed char,0x39D);
                        if(RIGHT(signed char,0x39D)>1) --RIGHT(signed char,0x39D);
                    }
                    FIELD(int,0x110)=FIELD(int,0x110)+1;
                }
                if(g_KeyScannerAt00671638.CheckKey(0x3E)) {
                    if(g_ReplayModeAt0066C238==1) {
                        g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                        int action4=4;g_ReplayEventsAt006718E0.Append(&action4);
                    }
                    FIELD(unsigned char,0x1C)=0;
                }
                if(g_KeyScannerAt00671638.CheckKey(0x3F)) {
                    if(g_ReplayModeAt0066C238==1) {
                        g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                        int action5=5;g_ReplayEventsAt006718E0.Append(&action5);
                    }
                    FIELD(unsigned char,0x1C)=1;
                }
                if(g_KeyScannerAt00671638.CheckKey(0x40)) {
                    if(g_ReplayModeAt0066C238==1) {
                        g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                        int action6=6;g_ReplayEventsAt006718E0.Append(&action6);
                    }
                    LEFT(float,0x36C)=LEFT(float,0x36C)+g_LevelStepAt00657850;
                    RIGHT(float,0x36C)=RIGHT(float,0x36C)+g_LevelStepAt00657850;
                    if(LEFT(float,0x36C)>g_LevelMaxAt00657B28) LEFT(float,0x36C)=900.0f;
                    if(RIGHT(float,0x36C)>g_LevelMaxAt00657B28) RIGHT(float,0x36C)=900.0f;
                }
                if(g_KeyScannerAt00671638.CheckKey(0x41)) {
                    if(g_ReplayModeAt0066C238==1) {
                        g_ReplayEventsAt006718E0.Append(&FIELD(int,0x14));
                        int action7=7;g_ReplayEventsAt006718E0.Append(&action7);
                    }
                    LEFT(float,0x36C)=LEFT(float,0x36C)-g_LevelStepAt00657850;
                    RIGHT(float,0x36C)=RIGHT(float,0x36C)-g_LevelStepAt00657850;
                    if(LEFT(float,0x36C)<g_LevelZeroAt0065782C) LEFT(float,0x36C)=0.0f;
                    if(RIGHT(float,0x36C)<g_LevelZeroAt0065782C) RIGHT(float,0x36C)=0.0f;
                }
            }
        }
        if(g_ReplayModeAt0066C238==2 && (g_KeyScannerAt00671638.CheckKey(0x1D) || g_KeyScannerAt00671638.CheckKey(0x9D))) {
            if(g_KeyScannerAt00671638.CheckKey(3)) NativeActionAt00423C60(8);
            else if(g_KeyScannerAt00671638.CheckKey(4)) NativeActionAt00423C60(6);
            else if(g_KeyScannerAt00671638.CheckKey(5)) NativeActionAt00423C60(4);
            else if(g_KeyScannerAt00671638.CheckKey(6)) NativeActionAt00423C60(3);
            else if(g_KeyScannerAt00671638.CheckKey(7)) NativeActionAt00423C60(2);
            else if(g_KeyScannerAt00671638.CheckKey(8)) NativeActionAt00423C60(1);
            else NativeActionAt00423C60(0x10);
        }
        if(g_ReplayModeAt0066C238==1 || g_ReplayModeAt0066C238==3) {
            if(g_KeyScannerAt00671638.CheckKey(0x1D) || g_KeyScannerAt00671638.CheckKey(0x9D) || g_InputGateAt00671678>5) g_InputCanCancelAt00671632=1;
            else g_InputCanCancelAt00671632=0;
        }
    }
}
#undef RIGHT
#undef LEFT
#undef FIELD
