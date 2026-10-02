// Game/Unsorted_10BC4200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BC4220
{
public:
    int FUN_10bc4220();

    char Unknown00[0x1C];
    int Unknown1C;
};

class Class_10BB8300
{
public:
    void FUN_10bb8300();
    bool FUN_10bb8c00();
};

class Class_10E8BE68
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10bc4200();

    Class_10BB8300* Unknown04;
};

// FUNCTION: 0x10BC4200 ?FUN_10bc4200@Class_10E8BE68@@UAEXXZ
void Class_10E8BE68::FUN_10bc4200()
{
    if (!Unknown04->FUN_10bb8c00())
        Unknown04->FUN_10bb8300();
}

// FUNCTION: 0x10BC4220 ?FUN_10bc4220@Class_10BC4220@@QAEHXZ
int Class_10BC4220::FUN_10bc4220()
{
    int Value = Unknown1C;
    if (Value)
    {
        Unknown1C = 0;
        return Value;
    }
    return 0;
}
