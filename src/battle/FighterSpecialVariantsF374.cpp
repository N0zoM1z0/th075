#include "engine/GameSharedState.hpp"
#include "characters/MeilingFighter.hpp"
#include "characters/SuikaFighter.hpp"
#include "characters/YukariFighter.hpp"
#include "characters/YuyukoFighter.hpp"
#include "characters/RemiliaFighter.hpp"
#include "characters/YoumuFighter.hpp"
#include "characters/PatchouliFighter.hpp"
#include "characters/SakuyaFighter.hpp"
#include "characters/MarisaFighter.hpp"
#include "characters/ReimuFighter.hpp"
#include "characters/AliceFighter.hpp"
// Complete real 10-case mode switch shared by eleven original fighter routines.
// Each independently retains its original seven semantic variant IDs.
// A 40-byte native switch table is compared in each routine, NOT CODE credited.
// Only borrowed +0x6E5 field and selected-effect-mode global are observed.
void ReimuFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=1;break;
  case 2: field6E5=3;break;
  case 3: field6E5=5;break;
  case 4: field6E5=2;break;
  case 5: field6E5=6;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void MarisaFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=3;break;
  case 2: field6E5=2;break;
  case 3: field6E5=4;break;
  case 4: field6E5=6;break;
  case 5: field6E5=0;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void SakuyaFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=0;break;
  case 2: field6E5=3;break;
  case 3: field6E5=1;break;
  case 4: field6E5=5;break;
  case 5: field6E5=7;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void AliceFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=1;break;
  case 2: field6E5=0;break;
  case 3: field6E5=2;break;
  case 4: field6E5=4;break;
  case 5: field6E5=5;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void PatchouliFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=1;break;
  case 2: field6E5=2;break;
  case 3: field6E5=3;break;
  case 4: field6E5=5;break;
  case 5: field6E5=7;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void YoumuFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=0;break;
  case 2: field6E5=1;break;
  case 3: field6E5=4;break;
  case 4: field6E5=2;break;
  case 5: field6E5=6;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void RemiliaFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=2;break;
  case 2: field6E5=1;break;
  case 3: field6E5=0;break;
  case 4: field6E5=5;break;
  case 5: field6E5=7;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void YuyukoFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=5;break;
  case 2: field6E5=1;break;
  case 3: field6E5=0;break;
  case 4: field6E5=2;break;
  case 5: field6E5=6;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void YukariFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=6;break;
  case 2: field6E5=3;break;
  case 3: field6E5=5;break;
  case 4: field6E5=1;break;
  case 5: field6E5=0;break;
  case 6: field6E5=7;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
void SuikaFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=2;break;
  case 2: field6E5=3;break;
  case 3: field6E5=5;break;
  case 4: field6E5=4;break;
  case 5: field6E5=1;break;
  case 6: field6E5=6;break;
  case 7:case 8:case 9:case 10: field6E5=0;break;
  }
}
void MeilingFighter::SelectVariant() {
  switch(g_StageAt0067161E) {
  case 1: field6E5=1;break;
  case 2: field6E5=3;break;
  case 3: field6E5=5;break;
  case 4: field6E5=2;break;
  case 5: field6E5=6;break;
  case 6: field6E5=8;break;
  case 7:case 8:case 9:case 10: field6E5=9;break;
  }
}
