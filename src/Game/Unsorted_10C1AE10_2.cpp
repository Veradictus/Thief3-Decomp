// Game/Unsorted_10C1AE10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAC050
{
public:
    int FUN_10bac050(int A);
};

struct Struct_10C1AE10
{
    char Unknown00[0x2C];
    int Unknown2C;
};

class Class_10E98D50
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
    virtual bool FUN_10c1ae10();

    int Unknown04;
    Class_10BAC050* Unknown08;
    char Unknown0C[0x3C];
    Struct_10C1AE10* Unknown48;
    bool Unknown4C;
};

// FUNCTION: 0x10C1AE10 ?FUN_10c1ae10@Class_10E98D50@@UAE_NXZ
bool Class_10E98D50::FUN_10c1ae10()
{
    if (!Unknown4C && Unknown04)
    {
        char Found = Unknown08->FUN_10bac050(Unknown04);
        bool Result;
        if (Unknown48->Unknown2C == 0x8000)
            Result = Found;
        else
            Result = !Found;
        return Result;
    }
    return false;
}
