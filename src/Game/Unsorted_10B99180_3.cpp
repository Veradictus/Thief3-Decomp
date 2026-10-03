// Game/Unsorted_10B99180_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10B98E00
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

int FUN_10bcba80();

extern float DAT_10eafbdc;

// 0x5c bytes; its constructor (0x10BCB8F0) stores the vtable 0x10E91EE8.
class Class_10E91EE8
{
public:
    Class_10E91EE8(int A, int B, int C);

    void** Unknown00;
    int Unknown04[22];
};

class Class_10E95288;

class Class_10E95898;

class Class_10BE5EF0;

class Class_10E93878;

class Class_10E96FD0;

class Class_10E4CCD0
{
public:
    virtual void Virtual0();
    virtual Class_10E95288* FUN_10b98e00(Struct_10B98E00* A);
    virtual void Virtual2();
    virtual Class_10E95898* FUN_10b98f60(Struct_10B98E00* A, int B, bool C);
    virtual void Virtual4();
    virtual Class_10BE5EF0* FUN_10b990d0(Struct_10B98E00* A);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual Class_10E91EE8* FUN_10b999e0(Struct_10B98E00* A, int B);
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual Class_10E93878* FUN_10b99ce0(Struct_10B98E00* A);
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual Class_10E96FD0* FUN_10b99470(Struct_10B98E00* A, int B);
};

// FUNCTION: 0x10B999E0 ?FUN_10b999e0@Class_10E4CCD0@@UAEPAVClass_10E91EE8@@PAUStruct_10B98E00@@H@Z
Class_10E91EE8* Class_10E4CCD0::FUN_10b999e0(Struct_10B98E00* A, int B)
{
    int Id = FUN_10bcba80();
    if (Id && A->Unknown08->FUN_10dbd510(Id)->FUN_10bbdb40() > DAT_10eafbdc)
        return new(0, 0, 0, 0, 0) Class_10E91EE8((int)A, (int)this, B);
    return 0;
}
