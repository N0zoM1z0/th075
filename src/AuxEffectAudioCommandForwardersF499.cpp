// Native whole call wrappers around original effect, audio, deque and
// shared fighter state. Only the physically observed own/class ABIs are
// expressed; borrowed game systems remain externally implemented.
class PeerFXManagerF499 {
public:
 void Spawn(short kind, int kindX, int kindY,
            unsigned char a, unsigned char b, unsigned char c,
            unsigned char d, const void* originalPosition);
};
class PeerFXOwnerF499 {
 unsigned char physicalOwnerPrefix[0x80];
 unsigned char physicalPosition[0x10];
 PeerFXManagerF499* linkedManager;
public:
 void SpawnPeer(short kind,int kindX,int kindY,unsigned char a,unsigned char b);
 void SpawnConfiguredPeer(short kind,int kindX,int kindY,unsigned char a,
                          unsigned char b,unsigned char c,unsigned char d);
};
void PeerFXOwnerF499::SpawnPeer(short kind,int kindX,int kindY,unsigned char a,unsigned char b){
 linkedManager->Spawn(kind,kindX,kindY,a,b,0,0,physicalPosition);
}
void PeerFXOwnerF499::SpawnConfiguredPeer(short kind,int kindX,int kindY,
                                         unsigned char a,unsigned char b,
                                         unsigned char c,unsigned char d){
 linkedManager->Spawn(kind,kindX,kindY,a,b,c,d,physicalPosition);
}
class SharedSoundFXF499 {public:void Play(int);};
extern SharedSoundFXF499* g_SharedSoundAt00671618;
class AudioForwarderF499 {public:void PlaySharedSound(short sound);};
void AudioForwarderF499::PlaySharedSound(short sound){
 g_SharedSoundAt00671618->Play(sound);
}
class NativeCommandDequeF499 {public:void Clear();};
class NativeCommandListF499 {
 unsigned int unknownNativeOwnerWord;
 NativeCommandDequeF499 entries;
public:void ClearEntries();
};
void NativeCommandListF499::ClearEntries(){entries.Clear();}
extern unsigned int g_SharedFighterValueAt00671628;
class BattleSceneSharedF499 {public:void SetSharedValue(unsigned int value);};
void BattleSceneSharedF499::SetSharedValue(unsigned int value){
 g_SharedFighterValueAt00671628=value;
}
