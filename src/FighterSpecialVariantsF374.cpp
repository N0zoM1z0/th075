// Complete real 10-case mode switch shared by eleven original fighter routines.
// Each independently retains its original seven semantic variant IDs.
// A 40-byte native switch table is compared in each routine, NOT CODE credited.
// Only borrowed +0x6E5 field and selected-effect-mode global are observed.
extern signed char g_SelectedEffectModeAt0067161E;
#define MODE (*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this)+0x6E5))
class ReimuFighterSpecialVariantF374 {public:void SelectVariant();};
void ReimuFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=1;break;
  case 2: MODE=3;break;
  case 3: MODE=5;break;
  case 4: MODE=2;break;
  case 5: MODE=6;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class MarisaFighterSpecialVariantF374 {public:void SelectVariant();};
void MarisaFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=3;break;
  case 2: MODE=2;break;
  case 3: MODE=4;break;
  case 4: MODE=6;break;
  case 5: MODE=0;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class SakuyaFighterSpecialVariantF374 {public:void SelectVariant();};
void SakuyaFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=0;break;
  case 2: MODE=3;break;
  case 3: MODE=1;break;
  case 4: MODE=5;break;
  case 5: MODE=7;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class AliceFighterSpecialVariantF374 {public:void SelectVariant();};
void AliceFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=1;break;
  case 2: MODE=0;break;
  case 3: MODE=2;break;
  case 4: MODE=4;break;
  case 5: MODE=5;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class PatchouliFighterSpecialVariantF374 {public:void SelectVariant();};
void PatchouliFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=1;break;
  case 2: MODE=2;break;
  case 3: MODE=3;break;
  case 4: MODE=5;break;
  case 5: MODE=7;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class YoumuFighterSpecialVariantF374 {public:void SelectVariant();};
void YoumuFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=0;break;
  case 2: MODE=1;break;
  case 3: MODE=4;break;
  case 4: MODE=2;break;
  case 5: MODE=6;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class RemiliaFighterSpecialVariantF374 {public:void SelectVariant();};
void RemiliaFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=2;break;
  case 2: MODE=1;break;
  case 3: MODE=0;break;
  case 4: MODE=5;break;
  case 5: MODE=7;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class YuyukoFighterSpecialVariantF374 {public:void SelectVariant();};
void YuyukoFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=5;break;
  case 2: MODE=1;break;
  case 3: MODE=0;break;
  case 4: MODE=2;break;
  case 5: MODE=6;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class YukariFighterSpecialVariantF374 {public:void SelectVariant();};
void YukariFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=6;break;
  case 2: MODE=3;break;
  case 3: MODE=5;break;
  case 4: MODE=1;break;
  case 5: MODE=0;break;
  case 6: MODE=7;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
class SuikaFighterSpecialVariantF374 {public:void SelectVariant();};
void SuikaFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=2;break;
  case 2: MODE=3;break;
  case 3: MODE=5;break;
  case 4: MODE=4;break;
  case 5: MODE=1;break;
  case 6: MODE=6;break;
  case 7:case 8:case 9:case 10: MODE=0;break;
  }
}
class MeilingFighterSpecialVariantF374 {public:void SelectVariant();};
void MeilingFighterSpecialVariantF374::SelectVariant() {
  switch(g_SelectedEffectModeAt0067161E) {
  case 1: MODE=1;break;
  case 2: MODE=3;break;
  case 3: MODE=5;break;
  case 4: MODE=2;break;
  case 5: MODE=6;break;
  case 6: MODE=8;break;
  case 7:case 8:case 9:case 10: MODE=9;break;
  }
}
#undef MODE
