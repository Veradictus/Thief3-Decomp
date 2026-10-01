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

struct Struct_10C15CC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

extern int DAT_10ff7068;

extern Struct_10C15CC0* DAT_10ff706c;

// FUNCTION: 0x10C15CC0 ?FUN_10c15cc0@@YA_NPAPAUStruct_10C15CC0@@HHHHH@Z
bool FUN_10c15cc0(Struct_10C15CC0** Out, int A, int B, int C, int D, int E)
{
    if (DAT_10ff7068 >= 0x400)
        return false;
    *Out = &DAT_10ff706c[DAT_10ff7068];
    (*Out)->Unknown0C = A;
    (*Out)->Unknown10 = B;
    (*Out)->Unknown14 = C;
    (*Out)->Unknown04 = D;
    (*Out)->Unknown08 = E;
    DAT_10ff7068++;
    return true;
}

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
