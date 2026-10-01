// Game/Unsorted_10B4F4E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B21570
{
public:
    bool FUN_10b21570();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Class_10B21570* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E7EB20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int FUN_10b4f4e0(int A);
};

// FUNCTION: 0x10B4F4E0 ?FUN_10b4f4e0@Class_10E7EB20@@UAEHH@Z
int Class_10E7EB20::FUN_10b4f4e0(int A)
{
    switch (A)
    {
    case 1:
        return DAT_10f35dec->Unknown08->FUN_10b21570() ? 0x15 : 0;
    default:
        return Virtual4();
    }
}
