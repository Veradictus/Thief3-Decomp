// Game/Unsorted_10BE9AC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB89D0;

class APawn
{
public:
    void FUN_10a6ea30(int Flags, int Value);
};

struct Struct_10BE9AC0
{
    char Unknown00[4];
    APawn* Unknown04;
};

class Class_10E94578
{
public:
    virtual void FUN_10be9ac0();

    void FUN_10bc5b50();
};

class Class_10E970F0 : public Class_10E94578
{
public:
    virtual void FUN_10be9ac0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10be9890();

    Class_10BB89D0* Unknown04;
    char Unknown08[0x58];
    Struct_10BE9AC0* Unknown60;
    char Unknown64[0x10];
    int Unknown74;
};

// FUNCTION: 0x10BE9AC0 ?FUN_10be9ac0@Class_10E970F0@@UAEXXZ
void Class_10E970F0::FUN_10be9ac0()
{
    if (!Unknown74 && Unknown60)
    {
        if (Unknown60->Unknown04)
            Unknown60->Unknown04->FUN_10a6ea30(0x800709, 0);
        delete Unknown60;
        Unknown60 = 0;
    }
}
