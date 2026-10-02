// Game/Unsorted_10C60D80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C60E60 {};

class Class_10E9CB00
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
    virtual void FUN_10c60e60();

    char Unknown04[0xC];
    int Unknown10;
    char Unknown14[0xE4];
    Struct_10C60E60* UnknownF8;
    int UnknownFC;
    char Unknown100[0x30];
    Struct_10C60E60* Unknown130;
};

// FUNCTION: 0x10C60E60 ?FUN_10c60e60@Class_10E9CB00@@UAEXXZ
void Class_10E9CB00::FUN_10c60e60()
{
    if (UnknownF8)
        Unknown10 -= UnknownFC;
    delete UnknownF8;
    UnknownF8 = 0;
    delete Unknown130;
    Unknown130 = 0;
}
