// Game/Unsorted_10A84820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

enum EFindName
{
    FNAME_Find = 0,
    FNAME_Add = 1
};

class FName
{
public:
    FName(const char* Name, EFindName FindType);

    unsigned long Value;
};

class Class_109022E0
{
public:
    char* Unknown00;
};

class Class_10A84CE0
{
public:
    void FUN_10a84ce0(const Class_109022E0& Name);

    char Unknown00[4];
    FName Unknown04;
};

class Class_10A84D70;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(Class_10A84D70* Obj, int A, int B, int C);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10A84D70
{
public:
    void FUN_10a84d70();

    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    bool Unknown14;
    bool Unknown15;
    char Unknown16[0x16];
    int Unknown2C;
    int Unknown30;
};

class Class_10E5D498
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual bool FUN_10a84cb0(const Class_109022E0& Name);

    FName Unknown04;
};

// FUNCTION: 0x10A84CB0 ?FUN_10a84cb0@Class_10E5D498@@UAE_NABVClass_109022E0@@@Z
bool Class_10E5D498::FUN_10a84cb0(const Class_109022E0& Name)
{
    const char* Text = Name.Unknown00 ? Name.Unknown00 : DAT_10e47660;
    return Unknown04.Value == FName(Text, FNAME_Add).Value;
}

// FUNCTION: 0x10A84CE0 ?FUN_10a84ce0@Class_10A84CE0@@QAEXABVClass_109022E0@@@Z
void Class_10A84CE0::FUN_10a84ce0(const Class_109022E0& Name)
{
    const char* Text = Name.Unknown00 ? Name.Unknown00 : DAT_10e47660;
    Unknown04 = FName(Text, FNAME_Add);
}

// FUNCTION: 0x10A84D70 ?FUN_10a84d70@Class_10A84D70@@QAEXXZ
void Class_10A84D70::FUN_10a84d70()
{
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown14 = false;
    Unknown15 = false;
    Unknown10 = 0;
    Unknown2C = 0;
    Unknown30 = -1;
    DAT_10f46da0->Virtual3(this, 0x26, -1, -1);
}
