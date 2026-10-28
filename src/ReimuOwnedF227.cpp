// Physical allocation carrier only, not the complete original owner class.
class ReimuGeneratedF227 {
    unsigned char nativeAllocation[0xe8];
public:
    ReimuGeneratedF227(void* fighter);
};
typedef char AssertReimuGenerated232F227[(sizeof(ReimuGeneratedF227)==0xe8)?1:-1];
class ReimuFactoryF227 {
public:
    void CreateOwnedObject(ReimuGeneratedF227** output);
};
void ReimuFactoryF227::CreateOwnedObject(ReimuGeneratedF227** output)
{
    *output = new ReimuGeneratedF227(this);
}
