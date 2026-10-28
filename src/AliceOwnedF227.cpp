// Physical allocation carrier only, not the complete original owner class.
class AliceGeneratedF227 {
    unsigned char nativeAllocation[0xe8];
public:
    AliceGeneratedF227(void* fighter);
};
typedef char AssertAliceGenerated232F227[(sizeof(AliceGeneratedF227)==0xe8)?1:-1];
class AliceFactoryF227 {
public:
    void CreateOwnedObject(AliceGeneratedF227** output);
};
void AliceFactoryF227::CreateOwnedObject(AliceGeneratedF227** output)
{
    *output = new AliceGeneratedF227(this);
}
