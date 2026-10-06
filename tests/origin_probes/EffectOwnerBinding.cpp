// Complete generic observations; no original fighter or manager layout is claimed.
struct FighterBindingObservation { unsigned long identity; };
struct EffectOwnerBindingObservation {
    FighterBindingObservation* fighter;
    void bind(FighterBindingObservation* value);
};
void EffectOwnerBindingObservation::bind(FighterBindingObservation* value) {
    fighter = value;
}
template<class Fighter> struct TemplateEffectOwnerBindingObservation {
    Fighter* fighter;
    void bind(Fighter* value) { fighter = value; }
};
void ObserveTemplateEffectBinding(
    TemplateEffectOwnerBindingObservation<FighterBindingObservation>& manager,
    FighterBindingObservation* fighter) {
    manager.bind(fighter);
}
struct ConstructedEffectReferenceObservation {
    FighterBindingObservation* fighter;
    ConstructedEffectReferenceObservation(FighterBindingObservation* value);
};
ConstructedEffectReferenceObservation::ConstructedEffectReferenceObservation(
    FighterBindingObservation* value) : fighter(value) {}
struct ImplicitEffectReferenceObservation { FighterBindingObservation* fighter; };
typedef ImplicitEffectReferenceObservation& (ImplicitEffectReferenceObservation::*
    EffectReferenceAssignmentObservation)(const ImplicitEffectReferenceObservation&);
EffectReferenceAssignmentObservation EffectReferenceAssignment =
    &ImplicitEffectReferenceObservation::operator=;
void AssignEffectReference(ImplicitEffectReferenceObservation& destination,
                           const ImplicitEffectReferenceObservation& source) {
    destination = source;
}
void WriteBorrowedFighterReference(FighterBindingObservation*& destination,
                                 FighterBindingObservation* value) {
    destination = value;
}
extern const unsigned long EffectOwnerBindingObservationSizes[] = {
    sizeof(FighterBindingObservation),sizeof(EffectOwnerBindingObservation),
    sizeof(TemplateEffectOwnerBindingObservation<FighterBindingObservation>),
    sizeof(ConstructedEffectReferenceObservation),sizeof(ImplicitEffectReferenceObservation)
};
