// Game/Unsorted_10BB0C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9E410
{
public:
    void FUN_10b9eee0();
};

struct Struct_10BB0B90_Unknown118
{
    char Unknown00[8];
    Class_10B9E410* Unknown08;
};

class Struct_10BB0B90
{
public:
    char Unknown00[0x118];
    Struct_10BB0B90_Unknown118* Unknown118;
};

Struct_10BB0B90* FUN_10bb0b90(int A);

class Class_10E8C7E8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10bb0c90(int A, int B, int C);
};

// FUNCTION: 0x10BB0C90 ?FUN_10bb0c90@Class_10E8C7E8@@UAEHHHH@Z
int Class_10E8C7E8::FUN_10bb0c90(int A, int B, int C)
{
    Struct_10BB0B90* Owner = FUN_10bb0b90(B);
    if (!Owner)
        return 0;
    Struct_10BB0B90_Unknown118* Info = Owner->Unknown118;
    if (!Info)
        return 0;
    Class_10B9E410* Obj = Info->Unknown08;
    if (!Obj)
        return 0;
    Obj->FUN_10b9eee0();
    return 1;
}
