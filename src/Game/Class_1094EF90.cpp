// Game/Class_1094EF90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Elem_1094EF90
{
    int Unknown00;
    char Unknown04[0x1C];
    int Unknown20;
    char Unknown24[4];
};

class Class_1094EF90
{
public:
    int FUN_1094ef90(int Index);

    char Unknown00[0x108];
    Elem_1094EF90* Unknown108;
};

// FUNCTION: 0x1094EF90 ?FUN_1094ef90@Class_1094EF90@@QAEHH@Z
int Class_1094EF90::FUN_1094ef90(int Index)
{
    return (Unknown108[Index].Unknown20 + (Unknown108[Index].Unknown20 & 1) + Unknown108[Index].Unknown00 * 2) * 16;
}
