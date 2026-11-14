#include "MeilingFighter.hpp"
#include "SuikaFighter.hpp"
#include "YukariFighter.hpp"
#include "YuyukoFighter.hpp"
#include "RemiliaFighter.hpp"
#include "PatchouliFighter.hpp"
#include "SakuyaFighter.hpp"
// Seven independently native-confirmed whole fighter-owned object factories.
// Original new footprint 0xE8 and each unique borrowed constructor are real.
// This type footprint does not assert any private member layout.

class SakuyaOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: SakuyaOwnedObjectF469(void* owner);
};
void SakuyaFighter::CreateOwnedObject(SakuyaOwnedObjectF469** out) {
    *out = new SakuyaOwnedObjectF469(this);
}

class PatchouliOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: PatchouliOwnedObjectF469(void* owner);
};
void PatchouliFighter::CreateOwnedObject(PatchouliOwnedObjectF469** out) {
    *out = new PatchouliOwnedObjectF469(this);
}

class RemiliaOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: RemiliaOwnedObjectF469(void* owner);
};
void RemiliaFighter::CreateOwnedObject(RemiliaOwnedObjectF469** out) {
    *out = new RemiliaOwnedObjectF469(this);
}

class YuyukoOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: YuyukoOwnedObjectF469(void* owner);
};
void YuyukoFighter::CreateOwnedObject(YuyukoOwnedObjectF469** out) {
    *out = new YuyukoOwnedObjectF469(this);
}

class YukariOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: YukariOwnedObjectF469(void* owner);
};
void YukariFighter::CreateOwnedObject(YukariOwnedObjectF469** out) {
    *out = new YukariOwnedObjectF469(this);
}

class SuikaOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: SuikaOwnedObjectF469(void* owner);
};
void SuikaFighter::CreateOwnedObject(SuikaOwnedObjectF469** out) {
    *out = new SuikaOwnedObjectF469(this);
}

class MeilingOwnedObjectF469 {
  unsigned char actualAllocatedBytes[0xE8];
public: MeilingOwnedObjectF469(void* owner);
};
void MeilingFighter::CreateOwnedObject(MeilingOwnedObjectF469** out) {
    *out = new MeilingOwnedObjectF469(this);
}
