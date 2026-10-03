// Game/Unsorted_10B97C40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BC9D40
{
public:
    bool FUN_10bc9d40();
};

class Class_10B9CAC0
{
public:
    Class_10BC9D40* FUN_10b9cac0(int A);
};

struct Struct_10B9BCA0
{
    char Unknown00[8];
    Class_10B9CAC0* Unknown08;
};

class Class_10B9BCA0
{
public:
    bool FUN_10b9bca0(int A);

    char Unknown00[0x118];
    Struct_10B9BCA0* Unknown118;
};

class Class_10B9BDA0_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
};

class Class_10FF667C
{
public:
    char Unknown00[0x14];
    Class_10B9BDA0_Member* Unknown14;
};

extern Class_10FF667C* DAT_10ff667c;

class AAIPawnController
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
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
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
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
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual void FUN_10b9bda0();
};

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

struct Struct_10B98E00;

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E93148 : public Class_10E90D70
{
public:
    Class_10E93148(int A, int B, int C, bool D);

    int Unknown40[3];
    int Unknown4C;
    int Unknown50;
    bool Unknown54;
    bool Unknown55;
};

class Class_10E4CCD0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual Class_10E93148* FUN_10b97d80(Struct_10B98E00* A, int B, bool C);
};

// FUNCTION: 0x10B97D80 ?FUN_10b97d80@Class_10E4CCD0@@UAEPAVClass_10E93148@@PAUStruct_10B98E00@@H_N@Z
Class_10E93148* Class_10E4CCD0::FUN_10b97d80(Struct_10B98E00* A, int B, bool C)
{
    return new(0, 0, 0, 0, 0) Class_10E93148((int)A, (int)this, B, C);
}

// FUNCTION: 0x10B9BCA0 ?FUN_10b9bca0@Class_10B9BCA0@@QAE_NH@Z
bool Class_10B9BCA0::FUN_10b9bca0(int A)
{
    if (Unknown118 == 0)
        return false;
    return Unknown118->Unknown08->FUN_10b9cac0(A)->FUN_10bc9d40();
}

// FUNCTION: 0x10B9BDA0 ?FUN_10b9bda0@AAIPawnController@@UAEXXZ
void AAIPawnController::FUN_10b9bda0()
{
    DAT_10ff667c->Unknown14->F1();
}
