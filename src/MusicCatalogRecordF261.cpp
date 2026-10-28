#include "MusicCatalogRecordF261.hpp"
#include <stdlib.h>

MusicCatalogRecordF261::MusicCatalogRecordF261() {
    counter=0;
    first=0;
    second=0;
    third=0;
}

MusicCatalogRecordF261::~MusicCatalogRecordF261() {
    counter=0;
    void* ownedFirst=first;
    free(ownedFirst);
    {
        void* ownedSecond=second;
        free(ownedSecond);
    }
    {
        void* ownedThird=third;
        free(ownedThird);
    }
}
