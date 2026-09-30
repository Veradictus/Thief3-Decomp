// Game/Class_10943710.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Elem_10943710
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_10943710
{
public:
    int* FUN_10943710(int Index);

    char Unknown00[0xF0];
    int UnknownF0;
    char UnknownF4[0x3C];
    Elem_10943710* Unknown130;
};

// FUNCTION: 0x10943710 ?FUN_10943710@Class_10943710@@QAEPAHH@Z
int* Class_10943710::FUN_10943710(int Index)
{
    if (Index < UnknownF0)
        return &Unknown130[Index].Unknown04;
    return 0;
}
