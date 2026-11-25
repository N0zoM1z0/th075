// Complete public-SDK policy observers do not recover original owner layouts.
#include <d3dx8.h>

struct RawSurfaceLease {
    ID3DXRenderToSurface* resource;
};
struct ExplicitSurfaceLease {
    ID3DXRenderToSurface* resource;
    ~ExplicitSurfaceLease() {
        if (resource) resource->OnLostDevice();
    }
};
struct ExplicitEnvMapLease {
    ID3DXRenderToEnvMap* resource;
    ~ExplicitEnvMapLease() {
        if (resource) resource->OnLostDevice();
    }
};
void ObserveRawSurfaceEnd(RawSurfaceLease* lease) {
    lease->~RawSurfaceLease();
}
void ObserveExplicitSurfaceEnd(ExplicitSurfaceLease* lease) {
    lease->~ExplicitSurfaceLease();
}
void ObserveExplicitEnvMapEnd(ExplicitEnvMapLease* lease) {
    lease->~ExplicitEnvMapLease();
}
extern "C" const unsigned long SDKReleasePolicyLayout[] = {
    sizeof(RawSurfaceLease), sizeof(ExplicitSurfaceLease), sizeof(ExplicitEnvMapLease)
};
