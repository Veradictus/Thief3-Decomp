// Game/Unsorted_10AC98C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AC99D0
{
public:
    int FUN_10ac99d0(int Index);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

// FUNCTION: 0x10AC99D0 ?FUN_10ac99d0@Class_10AC99D0@@QAEHH@Z
int Class_10AC99D0::FUN_10ac99d0(int Index)
{
    if (Index + 1 < Unknown04)
        return Unknown0C[Index + 1];
    return 0;
}
