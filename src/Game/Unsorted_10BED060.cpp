// Game/Unsorted_10BED060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e97258[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E97258 : public Class_10E90D70
{
public:
    Class_10E97258* FUN_10bed080(int A, int B, int C, int D, int E, int F);

    bool Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    int Unknown50;
};

void __stdcall FUN_109e3c90(int A);

class Class_10E97488
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
    virtual void FUN_10bed060(int A);

    char Unknown04[0x68];
    int Unknown6C;
};

// FUNCTION: 0x10BED060 ?FUN_10bed060@Class_10E97488@@UAEXH@Z
void Class_10E97488::FUN_10bed060(int A)
{
    FUN_109e3c90(A);
    if (Unknown6C == A)
        Unknown6C = 0;
}

// FUNCTION: 0x10BED080 ?FUN_10bed080@Class_10E97258@@QAEPAV1@HHHHHH@Z
Class_10E97258* Class_10E97258::FUN_10bed080(int A, int B, int C, int D, int E, int F)
{
    this->Class_10E90D70::Class_10E90D70(E, F);
    Unknown44 = A;
    Unknown48 = B;
    Unknown40 = 1;
    Unknown00 = DAT_10e97258;
    Unknown4C = C;
    Unknown50 = D;
    return this;
}
