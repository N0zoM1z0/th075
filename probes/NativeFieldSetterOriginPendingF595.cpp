// F595: original PE-only undecided-origin leaf 004135F0, no authored credit.
class NativeFieldSetterF595 { public: void WriteFields(unsigned char flag, unsigned int first, unsigned int second); };
void NativeFieldSetterF595::WriteFields(unsigned char flag,unsigned int first,unsigned int second) {
    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this)+0x24)=flag;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this)+0x1C)=first;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this)+0x20)=second;
}
