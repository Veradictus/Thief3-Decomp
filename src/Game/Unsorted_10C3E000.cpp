// Game/Unsorted_10C3E000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109BBBA0;

struct Arg_10A48720
{
    Arg_10A48720() { Unknown00 = 0; }
    Arg_10A48720(const Arg_10A48720& Other) { Unknown00 = Other.Unknown00; }

    int Unknown00;
};

void FUN_10a48720(int A, int* B, int C, int D, Class_109BBBA0* E, int F, Arg_10A48720 G);

class Class_10E9B240
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10c3e010(int A);

    void FUN_10c3d600(int A);

    char Unknown04[0x44];
    int Unknown48;
    int Unknown4C;
    int Unknown50;
    char Unknown54[0xC];
    int Unknown60;
    char Unknown64[0xC];
    Class_109BBBA0* Unknown70;
};

// FUNCTION: 0x10C3E010 ?FUN_10c3e010@Class_10E9B240@@UAEXH@Z
void Class_10E9B240::FUN_10c3e010(int A)
{
    FUN_10c3d600(A);
    Arg_10A48720 Flags;
    FUN_10a48720(A, &Unknown48, Unknown50, Unknown4C, Unknown70, Unknown60, Flags);
}
