// Original stage-specific constructors with native C++ inherited base
// construction, derived vtables, real /GX EH entry, asset string refs, and
// true stage camera data at observed offsets. Base/asset/quad interfaces are
// borrowed callable views only: no full stage object is embedded, allocated
// or claimed here. These two are independent original authored CODE extents.
class BackgroundBaseF376 {
public:
 BackgroundBaseF376();
 virtual ~BackgroundBaseF376();
};
class StageQuadF376 {public:void Initialize();};
class StagePackF376 {public: void AllocateUnformattedSlots(int);void ReadPack(const char*,const char*);};
extern const char g_BGDirectory00aF376[];
extern const char g_BGFilename00aF376[];
extern const char g_BGDirectory00bF376[];
extern const char g_BGFilename00bF376[];
class Background00aF376 : public BackgroundBaseF376 {
public:
 Background00aF376();
 virtual ~Background00aF376();
};
class Background00bF376 : public BackgroundBaseF376 {
public:
 Background00bF376();
 virtual ~Background00bF376();
};
#define FIELD(type, offset) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(offset)))
#define PACK (*reinterpret_cast<StagePackF376*>(reinterpret_cast<unsigned char*>(this)+0x18))
Background00aF376::Background00aF376() {
 reinterpret_cast<StageQuadF376*>(reinterpret_cast<unsigned char*>(this)+0x68)->Initialize();
 PACK.AllocateUnformattedSlots(3);
 PACK.ReadPack(g_BGFilename00aF376,g_BGDirectory00aF376);
 FIELD(int,0xc)=0; FIELD(int,0x10)=0; FIELD(int,0x14)=0;
}
Background00bF376::Background00bF376() {
 reinterpret_cast<StageQuadF376*>(reinterpret_cast<unsigned char*>(this)+0x6c)->Initialize();
 PACK.AllocateUnformattedSlots(4);
 PACK.ReadPack(g_BGFilename00bF376,g_BGDirectory00bF376);
 FIELD(int,0xc)=0; FIELD(int,0x10)=0; FIELD(int,0x14)=0;
 FIELD(int,0x68)=0;
}
#undef PACK
#undef FIELD
