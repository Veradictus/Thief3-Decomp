// Game/Unsorted_10C15BC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C15D40 {
public:
    char Unknown00[0x401C];
    void* Unknown401C;

    bool FUN_10c15d40();
};

class Class_10C15D20
{
public:
    void FUN_10c15d20(int A, int B, int C, int D);

    char Unknown00[4];
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    char Unknown10[4];
    int Unknown14;
};

// FUNCTION: 0x10C15D20 ?FUN_10c15d20@Class_10C15D20@@QAEXHHHH@Z
void Class_10C15D20::FUN_10c15d20(int A, int B, int C, int D)
{
    Unknown0C = A;
    Unknown14 = B;
    Unknown04 = C;
    Unknown08 = D;
}

// FUNCTION: 0x10C15D40 ?FUN_10c15d40@Class_10C15D40@@QAE_NXZ
bool Class_10C15D40::FUN_10c15d40()
{
    return Unknown401C == 0;
}
