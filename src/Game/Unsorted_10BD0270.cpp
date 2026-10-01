// Game/Unsorted_10BD0270.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E93710
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
    virtual void FUN_10bd17e0(int A);

    char Unknown04[0x3C];
    int Unknown40;
    char Unknown44[0xC0];
    int Unknown104;
};

extern void* DAT_10e93148[];

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
    Class_10E93148* FUN_10bd0990(int A, int B, int C, bool D);

    int Unknown40[3];
    int Unknown4C;
    int Unknown50;
    bool Unknown54;
    bool Unknown55;
};

// FUNCTION: 0x10BD0990 ?FUN_10bd0990@Class_10E93148@@QAEPAV1@HHH_N@Z
Class_10E93148* Class_10E93148::FUN_10bd0990(int A, int B, int C, bool D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e93148;
    for (int i = 0; i < 3; i++)
        Unknown40[i] = 0;
    Unknown4C = C;
    Unknown50 = 0;
    Unknown54 = D;
    Unknown55 = 0;
    return this;
}

// FUNCTION: 0x10BD17E0 ?FUN_10bd17e0@Class_10E93710@@UAEXH@Z
void Class_10E93710::FUN_10bd17e0(int A)
{
    if (Unknown104 == A)
        Unknown104 = 0;
    if (Unknown40 == A)
        Unknown40 = 0;
}
