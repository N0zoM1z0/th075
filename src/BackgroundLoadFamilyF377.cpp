// Independently target-reviewed complete native game stage constructors.
// This translation unit has only borrowed callable base/camera/pack APIs.
// Each constructor has genuine C++ /GX EH and original character-specific
// vtable, asset paths, camera offset, slot count and observed field values.
// No stage owner allocations or complete private class layout are asserted.
class StageBaseF377 {public:StageBaseF377();virtual ~StageBaseF377();};
class StageCameraF377 {public:void Initialize();};
class StageResourcePackF377 {public:void AllocateUnformattedSlots(int);void ReadPack(const char*,const char*);};
#define FIELD(type,off) (*reinterpret_cast<type*>(reinterpret_cast<unsigned char*>(this)+(off)))
#define CAMERA(off) reinterpret_cast<StageCameraF377*>(reinterpret_cast<unsigned char*>(this)+(off))
#define PACK (*reinterpret_cast<StageResourcePackF377*>(reinterpret_cast<unsigned char*>(this)+0x18))
extern const char g_DirectoryBG00cAt006584D8F377[];
extern const char g_FilenameBG00cAt006584E0F377[];
class BackgroundBG00cF377:public StageBaseF377 {public:BackgroundBG00cF377();virtual ~BackgroundBG00cF377();};
BackgroundBG00cF377::BackgroundBG00cF377() {
    CAMERA(0x68)->Initialize();
    PACK.AllocateUnformattedSlots(3);
    PACK.ReadPack(g_FilenameBG00cAt006584E0F377,g_DirectoryBG00cAt006584D8F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG00xAt00658514F377[];
extern const char g_FilenameBG00xAt0065851CF377[];
class BackgroundBG00xF377:public StageBaseF377 {public:BackgroundBG00xF377();virtual ~BackgroundBG00xF377();};
BackgroundBG00xF377::BackgroundBG00xF377() {
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG00xAt0065851CF377,g_DirectoryBG00xAt00658514F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG00yAt00658550F377[];
extern const char g_FilenameBG00yAt00658558F377[];
class BackgroundBG00yF377:public StageBaseF377 {public:BackgroundBG00yF377();virtual ~BackgroundBG00yF377();};
BackgroundBG00yF377::BackgroundBG00yF377() {
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG00yAt00658558F377,g_DirectoryBG00yAt00658550F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG00zAt0065858CF377[];
extern const char g_FilenameBG00zAt00658594F377[];
class BackgroundBG00zF377:public StageBaseF377 {public:BackgroundBG00zF377();virtual ~BackgroundBG00zF377();};
BackgroundBG00zF377::BackgroundBG00zF377() {
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG00zAt00658594F377,g_DirectoryBG00zAt0065858CF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG01aAt006585C8F377[];
extern const char g_FilenameBG01aAt006585D0F377[];
class BackgroundBG01aF377:public StageBaseF377 {public:BackgroundBG01aF377();virtual ~BackgroundBG01aF377();};
BackgroundBG01aF377::BackgroundBG01aF377() {
    CAMERA(0x68)->Initialize();
    PACK.AllocateUnformattedSlots(3);
    PACK.ReadPack(g_FilenameBG01aAt006585D0F377,g_DirectoryBG01aAt006585C8F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG01bAt00658610F377[];
extern const char g_FilenameBG01bAt00658618F377[];
class BackgroundBG01bF377:public StageBaseF377 {public:BackgroundBG01bF377();virtual ~BackgroundBG01bF377();};
BackgroundBG01bF377::BackgroundBG01bF377() {
    CAMERA(0x68)->Initialize();
    PACK.AllocateUnformattedSlots(3);
    PACK.ReadPack(g_FilenameBG01bAt00658618F377,g_DirectoryBG01bAt00658610F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG01xAt0065864CF377[];
extern const char g_FilenameBG01xAt00658654F377[];
class BackgroundBG01xF377:public StageBaseF377 {public:BackgroundBG01xF377();virtual ~BackgroundBG01xF377();};
BackgroundBG01xF377::BackgroundBG01xF377() {
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG01xAt00658654F377,g_DirectoryBG01xAt0065864CF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG01yAt00658688F377[];
extern const char g_FilenameBG01yAt00658690F377[];
class BackgroundBG01yF377:public StageBaseF377 {public:BackgroundBG01yF377();virtual ~BackgroundBG01yF377();};
BackgroundBG01yF377::BackgroundBG01yF377() {
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG01yAt00658690F377,g_DirectoryBG01yAt00658688F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG02aAt006586C4F377[];
extern const char g_FilenameBG02aAt006586CCF377[];
class BackgroundBG02aF377:public StageBaseF377 {public:BackgroundBG02aF377();virtual ~BackgroundBG02aF377();};
BackgroundBG02aF377::BackgroundBG02aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(5);
    PACK.ReadPack(g_FilenameBG02aAt006586CCF377,g_DirectoryBG02aAt006586C4F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG02bAt00658708F377[];
extern const char g_FilenameBG02bAt00658710F377[];
class BackgroundBG02bF377:public StageBaseF377 {public:BackgroundBG02bF377();virtual ~BackgroundBG02bF377();};
BackgroundBG02bF377::BackgroundBG02bF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(5);
    PACK.ReadPack(g_FilenameBG02bAt00658710F377,g_DirectoryBG02bAt00658708F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG02cAt00658744F377[];
extern const char g_FilenameBG02cAt0065874CF377[];
class BackgroundBG02cF377:public StageBaseF377 {public:BackgroundBG02cF377();virtual ~BackgroundBG02cF377();};
BackgroundBG02cF377::BackgroundBG02cF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(5);
    PACK.ReadPack(g_FilenameBG02cAt0065874CF377,g_DirectoryBG02cAt00658744F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG02xAt00658780F377[];
extern const char g_FilenameBG02xAt00658788F377[];
class BackgroundBG02xF377:public StageBaseF377 {public:BackgroundBG02xF377();virtual ~BackgroundBG02xF377();};
BackgroundBG02xF377::BackgroundBG02xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG02xAt00658788F377,g_DirectoryBG02xAt00658780F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG02yAt006587BCF377[];
extern const char g_FilenameBG02yAt006587C4F377[];
class BackgroundBG02yF377:public StageBaseF377 {public:BackgroundBG02yF377();virtual ~BackgroundBG02yF377();};
BackgroundBG02yF377::BackgroundBG02yF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG02yAt006587C4F377,g_DirectoryBG02yAt006587BCF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG02zAt006587F8F377[];
extern const char g_FilenameBG02zAt00658800F377[];
class BackgroundBG02zF377:public StageBaseF377 {public:BackgroundBG02zF377();virtual ~BackgroundBG02zF377();};
BackgroundBG02zF377::BackgroundBG02zF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG02zAt00658800F377,g_DirectoryBG02zAt006587F8F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG03aAt00658834F377[];
extern const char g_FilenameBG03aAt0065883CF377[];
class BackgroundBG03aF377:public StageBaseF377 {public:BackgroundBG03aF377();virtual ~BackgroundBG03aF377();};
BackgroundBG03aF377::BackgroundBG03aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(3);
    PACK.ReadPack(g_FilenameBG03aAt0065883CF377,g_DirectoryBG03aAt00658834F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG03bAt00658870F377[];
extern const char g_FilenameBG03bAt00658878F377[];
class BackgroundBG03bF377:public StageBaseF377 {public:BackgroundBG03bF377();virtual ~BackgroundBG03bF377();};
BackgroundBG03bF377::BackgroundBG03bF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(3);
    PACK.ReadPack(g_FilenameBG03bAt00658878F377,g_DirectoryBG03bAt00658870F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG03xAt006588ACF377[];
extern const char g_FilenameBG03xAt006588B4F377[];
class BackgroundBG03xF377:public StageBaseF377 {public:BackgroundBG03xF377();virtual ~BackgroundBG03xF377();};
BackgroundBG03xF377::BackgroundBG03xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG03xAt006588B4F377,g_DirectoryBG03xAt006588ACF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG03yAt006588E8F377[];
extern const char g_FilenameBG03yAt006588F0F377[];
class BackgroundBG03yF377:public StageBaseF377 {public:BackgroundBG03yF377();virtual ~BackgroundBG03yF377();};
BackgroundBG03yF377::BackgroundBG03yF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG03yAt006588F0F377,g_DirectoryBG03yAt006588E8F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG04aAt00658924F377[];
extern const char g_FilenameBG04aAt0065892CF377[];
class BackgroundBG04aF377:public StageBaseF377 {public:BackgroundBG04aF377();virtual ~BackgroundBG04aF377();};
BackgroundBG04aF377::BackgroundBG04aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG04aAt0065892CF377,g_DirectoryBG04aAt00658924F377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG04bAt006589C0F377[];
extern const char g_FilenameBG04bAt006589C8F377[];
class BackgroundBG04bF377:public StageBaseF377 {public:BackgroundBG04bF377();virtual ~BackgroundBG04bF377();};
BackgroundBG04bF377::BackgroundBG04bF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG04bAt006589C8F377,g_DirectoryBG04bAt006589C0F377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG04xAt00658A28F377[];
extern const char g_FilenameBG04xAt00658A30F377[];
class BackgroundBG04xF377:public StageBaseF377 {public:BackgroundBG04xF377();virtual ~BackgroundBG04xF377();};
BackgroundBG04xF377::BackgroundBG04xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG04xAt00658A30F377,g_DirectoryBG04xAt00658A28F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG04yAt00658A64F377[];
extern const char g_FilenameBG04yAt00658A6CF377[];
class BackgroundBG04yF377:public StageBaseF377 {public:BackgroundBG04yF377();virtual ~BackgroundBG04yF377();};
BackgroundBG04yF377::BackgroundBG04yF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG04yAt00658A6CF377,g_DirectoryBG04yAt00658A64F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG05aAt00658AA0F377[];
extern const char g_FilenameBG05aAt00658AA8F377[];
class BackgroundBG05aF377:public StageBaseF377 {public:BackgroundBG05aF377();virtual ~BackgroundBG05aF377();};
BackgroundBG05aF377::BackgroundBG05aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(4);
    PACK.ReadPack(g_FilenameBG05aAt00658AA8F377,g_DirectoryBG05aAt00658AA0F377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG05bAt00658B00F377[];
extern const char g_FilenameBG05bAt00658B08F377[];
class BackgroundBG05bF377:public StageBaseF377 {public:BackgroundBG05bF377();virtual ~BackgroundBG05bF377();};
BackgroundBG05bF377::BackgroundBG05bF377() {
    CAMERA(0x74)->Initialize();
    PACK.AllocateUnformattedSlots(18);
    PACK.ReadPack(g_FilenameBG05bAt00658B08F377,g_DirectoryBG05bAt00658B00F377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
    FIELD(unsigned int,0x6C)=0;
    FIELD(unsigned int,0x70)=0;
}
extern const char g_DirectoryBG05xAt00658B60F377[];
extern const char g_FilenameBG05xAt00658B68F377[];
class BackgroundBG05xF377:public StageBaseF377 {public:BackgroundBG05xF377();virtual ~BackgroundBG05xF377();};
BackgroundBG05xF377::BackgroundBG05xF377() {
    CAMERA(0x68)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG05xAt00658B68F377,g_DirectoryBG05xAt00658B60F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG05yAt00658B9CF377[];
extern const char g_FilenameBG05yAt00658BA4F377[];
class BackgroundBG05yF377:public StageBaseF377 {public:BackgroundBG05yF377();virtual ~BackgroundBG05yF377();};
BackgroundBG05yF377::BackgroundBG05yF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG05yAt00658BA4F377,g_DirectoryBG05yAt00658B9CF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG06aAt00658BD8F377[];
extern const char g_FilenameBG06aAt00658BE0F377[];
class BackgroundBG06aF377:public StageBaseF377 {public:BackgroundBG06aF377();virtual ~BackgroundBG06aF377();};
BackgroundBG06aF377::BackgroundBG06aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(5);
    PACK.ReadPack(g_FilenameBG06aAt00658BE0F377,g_DirectoryBG06aAt00658BD8F377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG06xAt00658C30F377[];
extern const char g_FilenameBG06xAt00658C38F377[];
class BackgroundBG06xF377:public StageBaseF377 {public:BackgroundBG06xF377();virtual ~BackgroundBG06xF377();};
BackgroundBG06xF377::BackgroundBG06xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG06xAt00658C38F377,g_DirectoryBG06xAt00658C30F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG07aAt00658C6CF377[];
extern const char g_FilenameBG07aAt00658C74F377[];
class BackgroundBG07aF377:public StageBaseF377 {public:BackgroundBG07aF377();virtual ~BackgroundBG07aF377();};
BackgroundBG07aF377::BackgroundBG07aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(4);
    PACK.ReadPack(g_FilenameBG07aAt00658C74F377,g_DirectoryBG07aAt00658C6CF377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG07xAt00658CD8F377[];
extern const char g_FilenameBG07xAt00658CE0F377[];
class BackgroundBG07xF377:public StageBaseF377 {public:BackgroundBG07xF377();virtual ~BackgroundBG07xF377();};
BackgroundBG07xF377::BackgroundBG07xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG07xAt00658CE0F377,g_DirectoryBG07xAt00658CD8F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG08aAt00658D14F377[];
extern const char g_FilenameBG08aAt00658D1CF377[];
class BackgroundBG08aF377:public StageBaseF377 {public:BackgroundBG08aF377();virtual ~BackgroundBG08aF377();};
BackgroundBG08aF377::BackgroundBG08aF377() {
    CAMERA(0x70)->Initialize();
    PACK.AllocateUnformattedSlots(54);
    PACK.ReadPack(g_FilenameBG08aAt00658D1CF377,g_DirectoryBG08aAt00658D14F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
    FIELD(unsigned int,0x68)=0;
    FIELD(unsigned int,0x6C)=0;
}
extern const char g_DirectoryBG08xAt00658D60F377[];
extern const char g_FilenameBG08xAt00658D68F377[];
class BackgroundBG08xF377:public StageBaseF377 {public:BackgroundBG08xF377();virtual ~BackgroundBG08xF377();};
BackgroundBG08xF377::BackgroundBG08xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG08xAt00658D68F377,g_DirectoryBG08xAt00658D60F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
extern const char g_DirectoryBG09aAt00658D9CF377[];
extern const char g_FilenameBG09aAt00658DA4F377[];
class BackgroundBG09aF377:public StageBaseF377 {public:BackgroundBG09aF377();virtual ~BackgroundBG09aF377();};
BackgroundBG09aF377::BackgroundBG09aF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(26);
    PACK.ReadPack(g_FilenameBG09aAt00658DA4F377,g_DirectoryBG09aAt00658D9CF377);
    FIELD(float,0xC)=640.0f;
    FIELD(float,0x10)=100.0f;
    FIELD(float,0x14)=100.0f;
    FIELD(unsigned int,0x68)=0;
}
extern const char g_DirectoryBG09xAt00658E30F377[];
extern const char g_FilenameBG09xAt00658E38F377[];
class BackgroundBG09xF377:public StageBaseF377 {public:BackgroundBG09xF377();virtual ~BackgroundBG09xF377();};
BackgroundBG09xF377::BackgroundBG09xF377() {
    CAMERA(0x6C)->Initialize();
    PACK.AllocateUnformattedSlots(2);
    PACK.ReadPack(g_FilenameBG09xAt00658E38F377,g_DirectoryBG09xAt00658E30F377);
    FIELD(unsigned int,0xC)=0;
    FIELD(unsigned int,0x10)=0;
    FIELD(unsigned int,0x14)=0;
}
#undef PACK
#undef CAMERA
#undef FIELD
