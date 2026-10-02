// Independent VC7.1 emission probe for a virtual scalar deleting destructor.
// The class and member policy are synthetic; no TH075 class layout is assumed.

class ProbeDeletingDestructor {
public:
    ProbeDeletingDestructor() : value_(0) {}
    virtual ~ProbeDeletingDestructor();

private:
    int value_;
};

ProbeDeletingDestructor::~ProbeDeletingDestructor() {
    value_ = 0;
}

extern "C" void ProbeDeleteObject(ProbeDeletingDestructor* object) {
    delete object;
}
