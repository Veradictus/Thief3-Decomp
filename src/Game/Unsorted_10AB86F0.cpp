// Game/Unsorted_10AB86F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AB86F0
{
    int Unknown00;
    int Unknown04;
    char Unknown08[0x28];
};

class Class_10AB86F0
{
public:
    int FUN_10ab86f0(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10AB86F0* Unknown0C;
};

// FUNCTION: 0x10AB86F0 ?FUN_10ab86f0@Class_10AB86F0@@QAEHH@Z
int Class_10AB86F0::FUN_10ab86f0(int A)
{
    int Index = -1;
    for (int i = 0; i < Unknown04; i++)
    {
        if (A == Unknown0C[i].Unknown00)
        {
            Index = i;
            break;
        }
    }
    if (Index >= 0)
        return Unknown0C[Index].Unknown04;
    return 0;
}
