// F665: four distinct full native linked CODE receiver-forwarding leaves.
// These are *compiler grammar probes*; original C++ names, object owner,
// destructor/lifetime status and authored-vs-library provenance UNKNOWN.
// No ASM, fake stack locals, imported original bytes, or hidden padding.
class ForwarderOwnerA_F665 {public: void Forward();void Inner();};
class ForwarderOwnerB_F665 {public: void Forward();void Inner();};
class ForwarderOwnerC_F665 {public: void Forward();void Inner();};
class ForwarderOwnerD_F665 {public: void Forward();void Inner();};
void ForwarderOwnerA_F665::Forward(){Inner();}
void ForwarderOwnerB_F665::Forward(){Inner();}
void ForwarderOwnerC_F665::Forward(){Inner();}
void ForwarderOwnerD_F665::Forward(){Inner();}
