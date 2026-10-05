// Complete generic observation owners, not reconstructed game layouts.
#include <vector>
#include <new>

struct FrameRecordObservation {
    void* image;
    short duration;
};

typedef std::vector<FrameRecordObservation> FrameSequenceObservation;
typedef std::vector<FrameSequenceObservation*> FrameCatalogObservation;

class VirtualFrameObservation {
public:
    virtual void Bind();
    FrameCatalogObservation* catalog;
    short sequence;
    short frame;
    FrameRecordObservation* selected;
    FrameRecordObservation* current;
    short duration;
    short count;
    FrameSequenceObservation* currentSequence;
};

void VirtualFrameObservation::Bind() {
    selected = &catalog->at(sequence)->at(frame);
    current = selected;
    duration = selected->duration;
    count = static_cast<short>(catalog->at(sequence)->size());
    currentSequence = catalog->at(sequence);
}

class GenericAssetViewObservation {
public:
    virtual void Bind();
    FrameCatalogObservation* catalog;
    short sequence;
    short frame;
    FrameRecordObservation* selected;
    FrameRecordObservation* current;
    short duration;
    short count;
    FrameSequenceObservation* currentSequence;
};

void GenericAssetViewObservation::Bind() {
    selected = &catalog->at(sequence)->at(frame);
    current = selected;
    duration = selected->duration;
    count = static_cast<short>(catalog->at(sequence)->size());
    currentSequence = catalog->at(sequence);
}

class ImplicitFrameObservation : public VirtualFrameObservation {};

extern "C" void ConstructImplicitFrameObservation(ImplicitFrameObservation* owner) {
    new (owner) ImplicitFrameObservation;
}

extern "C" void InvokeFrameObservation(VirtualFrameObservation* owner) {
    owner->Bind();
}

extern const unsigned long VirtualFrameLayout[] = {
    sizeof(FrameRecordObservation), sizeof(FrameSequenceObservation),
    sizeof(FrameCatalogObservation), sizeof(VirtualFrameObservation),
    sizeof(GenericAssetViewObservation), sizeof(ImplicitFrameObservation)
};
