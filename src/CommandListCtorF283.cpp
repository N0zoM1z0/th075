#include <windows.h>
// Observed local resource-list construction at +4; the original complete
// private command container layout and owner names remain unproven.
class CommandQueueF283 {
    unsigned int observedWords[3];
public:
    CommandQueueF283();
    ~CommandQueueF283();
};
class CommandListF283 {
    void* texture;
    CommandQueueF283 queue;
    unsigned char mode;
    short capacity;
public:
    CommandListF283(void* source);
    void Reset();
};
CommandListF283::CommandListF283(void* source)
{
    texture=source;
    capacity=15;
    mode=5;
    Reset();
}
