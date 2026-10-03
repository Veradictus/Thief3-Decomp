// Game/Unsorted_10BE3060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a50(const Struct_10C05A50* A, const Struct_10C05A50* B);

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BE31B0_Target
{
    char Unknown00[0x2C];
    Struct_10C05A50 Unknown2C;
};

struct Struct_10BE31B0_Owner
{
    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

struct Struct_10BE31B0_Out
{
    char Unknown00[0xC];
};

class Class_10BE31B0
{
public:
    Struct_10C05A50* FUN_10be3060(Struct_10BE31B0_Out* Out);
    int FUN_10be31b0();

    char Unknown00[4];
    Struct_10BE31B0_Owner* Unknown04;
};

class Class_10E94578
{
public:
    virtual void Virtual0();

    void FUN_10bc5b50();
};

class Class_10BB8620
{
public:
    void FUN_10bb8620();
};

class Class_10BB85E0 : public Class_10BB8620
{
public:
    void FUN_10bb8ee0(int A);
};

class Class_10E95D00 : public Class_10E94578
{
public:
    bool FUN_10be3220();
    void FUN_10be38e0();
    void FUN_10be3df0();

    Class_10BB85E0* Unknown04;
    char Unknown08[0x38];
    bool Unknown40;
    char Unknown41[0x1B];
    int Unknown5C;
};

// FUNCTION: 0x10BE31B0 ?FUN_10be31b0@Class_10BE31B0@@QAEHXZ
int Class_10BE31B0::FUN_10be31b0()
{
    Struct_10BE31B0_Out Out;
    Class_10c7d570* Obj = Unknown04->Unknown08;
    if (FUN_10c05a50(&((Struct_10BE31B0_Target*)Obj->FUN_10c7d570())->Unknown2C, FUN_10be3060(&Out)) < 12544.0f)
        return 1;
    return 0;
}

// FUNCTION: 0x10BE3DF0 ?FUN_10be3df0@Class_10E95D00@@QAEXXZ
void Class_10E95D00::FUN_10be3df0()
{
    if (FUN_10be3220())
    {
        Unknown04->FUN_10bb8620();
        FUN_10bc5b50();
    }
    else if (!Unknown40)
    {
        if (Unknown5C > 8)
        {
            Unknown04->FUN_10bb8ee0(0);
            FUN_10bc5b50();
        }
        else
            FUN_10be38e0();
    }
}
