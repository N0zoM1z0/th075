// Explicit 232-byte allocation operand; borrowed receiver, not full owner layout.
class YoumuGeneratedF224 {
    unsigned char observedBytes[0xe8];
public:
    YoumuGeneratedF224(void* fighter);
};
typedef char VerifyYoumuNew232F224[(sizeof(YoumuGeneratedF224)==0xe8)?1:-1];
class YoumuFactoryF224 {
public:
    void CreateOwnedObject(YoumuGeneratedF224** output);
};
void YoumuFactoryF224::CreateOwnedObject(YoumuGeneratedF224** output)
{
    *output = new YoumuGeneratedF224(this);
}
