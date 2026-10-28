// Original native fighter script initialization of 1,000 physical indices
// and a borrowed script-entry container; not the full private script layout.
class ScriptEntriesF430 {
public:
    ScriptEntriesF430();
    ~ScriptEntriesF430();
    void Clear();
private:
    unsigned char borrowedStorage[20];
};
class FighterScriptF430 {
    short physicalPatternIndex[1000];
    ScriptEntriesF430 entries;
public:
    FighterScriptF430();
};
typedef char CheckIndexOffsetF430[(sizeof(short)*1000==0x7D0)?1:-1];
FighterScriptF430::FighterScriptF430() {
    entries.Clear();
    for(int index=0;index<1000;++index) physicalPatternIndex[index]=-1;
}
