#include "EventQueue.hpp"

EventQueue g_EventServiceQueueAt0068BE44;

void EventQueueGuardF457::AppendUnique(HANDLE* event) {
    unsigned char add = 1;
    for(unsigned int index=0; index<g_EventServiceQueueAt0068BE44.size(); ++index) {
        if (g_EventServiceQueueAt0068BE44.at(index)==event) {
            add=0;
        }
    }
    if(add) g_EventServiceQueueAt0068BE44.push_back(event);
}
