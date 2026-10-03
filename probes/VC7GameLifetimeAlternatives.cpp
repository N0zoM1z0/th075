// Synthetic emission alternatives; no TH075 owner layout is recovered here.
struct Leaf { Leaf(); ~Leaf(); int field; };
struct ExplicitWrapper { Leaf member; ExplicitWrapper(); ~ExplicitWrapper(); };
ExplicitWrapper::ExplicitWrapper() {}
ExplicitWrapper::~ExplicitWrapper() {}
struct ImplicitWrapper { Leaf member; };
extern "C" void Wrappers() { ExplicitWrapper a; ImplicitWrapper b; }
struct Geometry { Geometry(); };
struct ExplicitGeometry { int leading; Geometry member; ExplicitGeometry(); };
ExplicitGeometry::ExplicitGeometry() {}
struct ImplicitGeometry { int leading; Geometry member; };
extern "C" void Geometries() { ExplicitGeometry a; ImplicitGeometry b; }
struct State { State(); int field; };
struct ExplicitScene { virtual ~ExplicitScene(); State member; ExplicitScene(); };
ExplicitScene::ExplicitScene() {}
ExplicitScene::~ExplicitScene() {}
struct ImplicitScene { virtual ~ImplicitScene(); State member; };
ImplicitScene::~ImplicitScene() {}
extern "C" void Scenes() { ExplicitScene a; ImplicitScene b; }
// The target calls camera construction at +4 and texture construction at +24.
// These synthetic intervening scalars test that spacing only; the camera
// target writes globals, so this is not a claim about its object size.
struct Camera { Camera(); };
struct Texture { Texture(); ~Texture(); int field; };
struct ExplicitStage { virtual ~ExplicitStage(); Camera camera; int intervening[4]; Texture textures; ExplicitStage(); };
ExplicitStage::ExplicitStage() {}
ExplicitStage::~ExplicitStage() {}
struct InlineStage { virtual ~InlineStage() {} Camera camera; int intervening[4]; Texture textures; };
// An out-of-line virtual method forces construction and implicit cleanup.
struct AutomaticStage { virtual void Method(); Camera camera; int intervening[4]; Texture textures; };
void AutomaticStage::Method() {}
extern "C" void Stages() { ExplicitStage a; InlineStage b; AutomaticStage c; }
struct VirtualBase { virtual ~VirtualBase(); };
VirtualBase::~VirtualBase() {}
struct ImplicitVirtualStage : VirtualBase { Camera camera; int intervening[4]; Texture textures; };
extern "C" void VirtualStages() { ImplicitVirtualStage a; }
