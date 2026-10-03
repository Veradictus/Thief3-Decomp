// Game/Unsorted_10BDB230.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10E94578 : public Class_10BC4160
{
public:
    virtual void Virtual1();

    void FUN_10bc5b50();
};

class Object_10BDB230
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10E94A00 : public Class_10E94578
{
public:
    virtual void FUN_10bdb230();

    char Unknown04[0x3C];
    Object_10BDB230* Unknown40;
};

// FUNCTION: 0x10BDB230 ?FUN_10bdb230@Class_10E94A00@@UAEXXZ
void Class_10E94A00::FUN_10bdb230()
{
    if (Unknown40)
        Unknown40->Virtual2();
    if (FUN_10bc4160()->FUN_10aa82d0() == 0)
        FUN_10bc5b50();
}
