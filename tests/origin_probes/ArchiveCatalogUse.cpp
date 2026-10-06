#include <deque>
#include <new>
// Complete generic observations; original private archive owners are undeclared.
struct ArchiveHandleObservation { unsigned token; };
extern unsigned CatalogObservationUsers;
extern std::deque<ArchiveHandleObservation*> CatalogObservationHandles;
extern std::deque<char*> CatalogObservationNames;
struct CatalogUserObservation { CatalogUserObservation(); };
CatalogUserObservation::CatalogUserObservation() {
    if (CatalogObservationUsers == 0) {
        CatalogObservationHandles.clear();
        CatalogObservationNames.clear();
    }
    ++CatalogObservationUsers;
}
struct TemplateCatalogTag {};
template<class Tag> struct CatalogUseTemplateObservation {
    CatalogUseTemplateObservation() {
        if (CatalogObservationUsers == 0) {
            CatalogObservationHandles.clear();
            CatalogObservationNames.clear();
        }
        ++CatalogObservationUsers;
    }
};
template struct CatalogUseTemplateObservation<TemplateCatalogTag>;
struct ImplicitCatalogUserObservation {
    std::deque<ArchiveHandleObservation*> handles;
    std::deque<char*> names;
};
ImplicitCatalogUserObservation* ConstructImplicitCatalogUse(void* storage) {
    return new(storage) ImplicitCatalogUserObservation;
}
void DestroyImplicitCatalogUse(ImplicitCatalogUserObservation* value) {
    value->~ImplicitCatalogUserObservation();
}
extern const unsigned long ArchiveCatalogObservationSizes[] = {
    sizeof(CatalogUserObservation),
    sizeof(CatalogUseTemplateObservation<TemplateCatalogTag>),
    sizeof(CatalogObservationHandles),sizeof(CatalogObservationNames),
    sizeof(ImplicitCatalogUserObservation),sizeof(ArchiveHandleObservation)
};
