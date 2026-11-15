// Eleven independently native-exact original character auxiliary object
// constructors, complete R050 observed 134/146-byte original CODE each.
// Every derived native vtable address and the true borrowed base ctor
// target were physically checked against this original PE. The returned
// pointers and +0xD8..0xE2 shorts retain actual per-character differences.
#include "CharacterObject.hpp"

ReimuObject::ReimuObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
}

MarisaObject::MarisaObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

SakuyaObject::SakuyaObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

AliceObject::AliceObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

PatchouliObject::PatchouliObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

YoumuObject::YoumuObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

RemiliaObject::RemiliaObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

YuyukoObject::YuyukoObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

YukariObject::YukariObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

SuikaObject::SuikaObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
    field0E2=0;
}

MeilingObject::MeilingObject(void* ownerFighter) {
    owner=static_cast<Fighter*>(ownerFighter);
    drawing=static_cast<Fighter*>(ownerFighter)->drawing;
    sequences=&static_cast<Fighter*>(ownerFighter)->sequenceSlots;
    field0D8=0;
    field0DA=0;
    field0DC=0;
    field0DE=0;
    field0E0=0;
}
