// Complete generic list owners retain meaningful existing fields.
#include "VC7ListPolicyDependencies.cpp"
struct SpriteRenderParametersObservation : ListOwnerObservation {
    unsigned long colorMask;
    void setMode(unsigned char value);
    void setColorMask(unsigned long value);
};
void SpriteRenderParametersObservation::setMode(unsigned char value) {
    mode = value;
}
void SpriteRenderParametersObservation::setColorMask(unsigned long value) {
    colorMask = value;
}
template<class Tag> struct TemplateSpriteRenderParametersObservation : ListOwnerObservation {
    unsigned long colorMask;
    void setMode(unsigned char value) { mode = value; }
    void setColorMask(unsigned long value) { colorMask = value; }
};
struct SpriteParameterTag {};
void ObserveTemplateSpriteParameters(TemplateSpriteRenderParametersObservation<SpriteParameterTag>& owner,
                                    unsigned char mode, unsigned long colorMask) {
    owner.setMode(mode);
    owner.setColorMask(colorMask);
}
void WriteBorrowedMode(unsigned char& field, unsigned char value) { field = value; }
void WriteBorrowedMask(unsigned long& field, unsigned long value) { field = value; }
extern const unsigned long SpriteRenderParameterObservationSizes[] = {
    sizeof(ListOwnerObservation),sizeof(SpriteRenderParametersObservation),
    sizeof(TemplateSpriteRenderParametersObservation<SpriteParameterTag>),sizeof(SpriteParameterTag)
};
