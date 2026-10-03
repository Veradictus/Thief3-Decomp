// Game/Unsorted_10BE1DC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08940
{
public:
    int FUN_10c08940();
};

class Class_10978090
{
public:
    Class_10C08940* FUN_10978090();
};

class Class_10FF667C
{
public:
    char Unknown00[0x24];
    Class_10978090* Unknown24;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10BC4160
{
public:
    virtual void Virtual0();
};

class Class_10E94578 : public Class_10BC4160
{
public:
    virtual void Virtual1();

    void FUN_10bc5b50();
};

class Class_10E95AC8 : public Class_10E94578
{
public:
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10be1dc0();
};

// FUNCTION: 0x10BE1DC0 ?FUN_10be1dc0@Class_10E95AC8@@UAEXXZ
void Class_10E95AC8::FUN_10be1dc0()
{
    if (!DAT_10ff667c->Unknown24->FUN_10978090() || !DAT_10ff667c->Unknown24->FUN_10978090()->FUN_10c08940())
        FUN_10bc5b50();
}
