// Whole original character resource derived C++ dtor: real original
// vtable, physically native +0xFEC container, reverse owned lifetime.
class NativeCharacterResourcesBaseF492 {public:virtual ~NativeCharacterResourcesBaseF492();};
class CharacterEntryListF492 {public:void Clear();~CharacterEntryListF492();};
class CharacterResourcesF492:public NativeCharacterResourcesBaseF492 {
 unsigned char untypedPhysicalOwnerBytes[0xFE8];
 CharacterEntryListF492 entries;
public:virtual ~CharacterResourcesF492();
};
CharacterResourcesF492::~CharacterResourcesF492() {
 entries.Clear();
}
