// Game/Unsorted_10B49450.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B4A260
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10E7E730
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
    virtual void FUN_10b4a260(Struct_10B4A260* Out);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10B4A260 ?FUN_10b4a260@Class_10E7E730@@UAEXPAUStruct_10B4A260@@@Z
void Class_10E7E730::FUN_10b4a260(Struct_10B4A260* Out)
{
    if (Unknown10 == 1)
    {
        Out->Unknown00 = 0x3f9c;
        Out->Unknown04 = 0x6e38;
        Out->Unknown08 = -0x4000;
        Out->Unknown0C = 0x3000;
        Out->Unknown10 = 0x3000;
    }
    else
    {
        Out->Unknown00 = 0x3f9c;
        Out->Unknown04 = -0x4000;
        Out->Unknown08 = 0x6e38;
        Out->Unknown0C = 0x3000;
        Out->Unknown10 = 0x3000;
    }
}
