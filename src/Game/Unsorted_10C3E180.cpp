// Game/Unsorted_10C3E180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109BBBA0;

struct Arg_10A48720
{
    Arg_10A48720() { Unknown00 = 0; }
    Arg_10A48720(const Arg_10A48720& Other) { Unknown00 = Other.Unknown00; }

    int Unknown00;
};

void FUN_10a48720(int A, int* B, int C, int D, Class_109BBBA0* E, int F, Arg_10A48720 G);

class Class_10E9B370
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10c3e2d0(int A);

    char Unknown04[0x14];
    bool Unknown18;
    char Unknown19[0xF];
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    char Unknown34[0xC];
    int Unknown40;
    char Unknown44[0xC];
    Class_109BBBA0* Unknown50;
};

// FUNCTION: 0x10C3E2D0 ?FUN_10c3e2d0@Class_10E9B370@@UAEXH@Z
void Class_10E9B370::FUN_10c3e2d0(int A)
{
    Arg_10A48720 Flags;
    FUN_10a48720(A, &Unknown28, Unknown30, Unknown2C, Unknown50, Unknown40, Flags);
}
