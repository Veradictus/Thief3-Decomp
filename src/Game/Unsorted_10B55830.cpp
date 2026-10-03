// Game/Unsorted_10B55830.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B56210
{
public:
    virtual void Virtual0();
    virtual bool Virtual1(int A, int B, int C);
};

class Class_10E81DE8
{
public:
    virtual void Virtual0();
    virtual bool FUN_10b56210(int A, int B, int C);

    char Unknown04[0x1CC];
    Object_10B56210* Unknown1D0;
};

class Class_10B559A0
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
    virtual void Virtual56(int A);

    void FUN_10b55830();
    void FUN_10b55930();
    void FUN_10b559a0(int A, int B);

    char Unknown04[0xE0];
    int Unknown0E4;
};

// FUNCTION: 0x10B559A0 ?FUN_10b559a0@Class_10B559A0@@QAEXHH@Z
void Class_10B559A0::FUN_10b559a0(int A, int B)
{
    switch (A)
    {
    case 2:
        FUN_10b55930();
        break;
    case 3:
        Virtual56(2);
        FUN_10b55830();
        break;
    }
    Unknown0E4 = A;
}

// FUNCTION: 0x10B56210 ?FUN_10b56210@Class_10E81DE8@@UAE_NHHH@Z
bool Class_10E81DE8::FUN_10b56210(int A, int B, int C)
{
    if (Unknown1D0 && Unknown1D0->Virtual1(A, B, C))
        return true;
    return false;
}
