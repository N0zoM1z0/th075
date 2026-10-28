// Complete original R018 96-byte game-wide event enqueue. The native
// signature is cdecl with ordinary RET, not a thiscall. Duplicates merely
// clear the actual one-byte add flag; the original *continues scanning*
// every remaining element rather than breaking. All six physical native
// deque/global references were checked independently.
// Full originally authored 96-byte native event queue append-if-absent.
// The 20-byte borrowed global event list uses true unsigned size/index,
// and the actual native 1-byte found flag remains an original live local.
class EventWordDequeF457 {
public:
    unsigned int Size();
    unsigned int* At(unsigned int index);
    void PushBack(const unsigned int* entry);
};
extern EventWordDequeF457 g_EventQueueAt0068BE44;
namespace EventQueueGuardF457 {void AppendUnique(unsigned int event);}
void EventQueueGuardF457::AppendUnique(unsigned int event) {
    unsigned char add = 1;
    for(unsigned int index=0; index<g_EventQueueAt0068BE44.Size(); ++index) {
        if (*g_EventQueueAt0068BE44.At(index)==event) {
            add=0;
        }
    }
    if(add) g_EventQueueAt0068BE44.PushBack(&event);
}
