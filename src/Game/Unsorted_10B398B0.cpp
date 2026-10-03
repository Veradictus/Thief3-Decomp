// Game/Unsorted_10B398B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B21560
{
public:
    unsigned char FUN_10b21560();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Class_10B21560* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10B39AB0
{
public:
    float FUN_10b39ab0();

    char Unknown00[0xC];
    float Unknown0C;
    char Unknown10[0xC];
    float Unknown1C;
};

class Class_10BFBD70
{
public:
    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B48220
{
public:
    void FUN_10b48220(Class_10BFBD70* A, int B, int C);
};

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int A);

    char Unknown00[0x1C];
    int Unknown1C;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B399B0
{
public:
    void FUN_10b399b0(Class_10BFBD70* A, int B, int C);

    char Unknown00[0xC];
    Class_10B48220* Unknown0C[1];
};

class Class_10B47C90
{
public:
    void FUN_10b47c90(int A);
};

class Class_10B39A70_Unknown08
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
    virtual void Virtual55(int A);
};

class Class_10B39A70
{
public:
    void FUN_10b399f0();
    void FUN_10b39a70(int A);

    char Unknown00[8];
    Class_10B39A70_Unknown08* Unknown08;
    Class_10B47C90* Unknown0C[8];
};

// FUNCTION: 0x10B399B0 ?FUN_10b399b0@Class_10B399B0@@QAEXPAVClass_10BFBD70@@HH@Z
void Class_10B399B0::FUN_10b399b0(Class_10BFBD70* A, int B, int C)
{
    if (A->Unknown00 > 0)
    {
        int Index = FUN_10b3abf0()->FUN_10b3a460(A->Unknown08[A->Unknown00 - 1])->Unknown1C;
        Unknown0C[Index]->FUN_10b48220(A, B, C);
    }
}

// FUNCTION: 0x10B39A70 ?FUN_10b39a70@Class_10B39A70@@QAEXH@Z
void Class_10B39A70::FUN_10b39a70(int A)
{
    FUN_10b399f0();
    for (int i = 0; i < 8; i++)
        Unknown0C[i]->FUN_10b47c90(A);
    Unknown08->Virtual55(A);
}

// FUNCTION: 0x10B39AB0 ?FUN_10b39ab0@Class_10B39AB0@@QAEMXZ
float Class_10B39AB0::FUN_10b39ab0()
{
    if (!DAT_10f35dec->Unknown08->FUN_10b21560())
        return Unknown0C;
    return Unknown1C;
}
