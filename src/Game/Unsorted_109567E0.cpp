// Game/Unsorted_109567E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10953590
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

    void FUN_10953590();
};

class Class_10E4AE20 : public Class_10953590
{
public:
    virtual void FUN_109567e0();

    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0x14];
    int Unknown24;
    char Unknown28[0xC];
    int Unknown34;
    char Unknown38[0x14];
    bool Unknown4C;
    char Unknown4D[0x247];
    int Unknown294;
    int Unknown298;
    int Unknown29C;
    float Unknown2A0;
};

// FUNCTION: 0x109567E0 ?FUN_109567e0@Class_10E4AE20@@UAEXXZ
void Class_10E4AE20::FUN_109567e0()
{
    FUN_10953590();
    Unknown294 = 0;
    Unknown298 = 0;
    Unknown29C = 0;
    Unknown2A0 = 1.0f;
    switch (Unknown0C)
    {
    case 1:
        Unknown24 = 0;
        Unknown4C = true;
        Unknown34 = 4;
        break;
    default:
        Unknown34 = 0;
        break;
    }
}
