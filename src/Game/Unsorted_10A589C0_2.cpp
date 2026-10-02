// Game/Unsorted_10A589C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A58B70
{
public:
    int FUN_10a58b70(int Index);

    char Unknown00[0x154];
    int Unknown154;
    int Unknown158;
    int* Unknown15C;
};

// FUNCTION: 0x10A58B70 ?FUN_10a58b70@Class_10A58B70@@QAEHH@Z
int Class_10A58B70::FUN_10a58b70(int Index)
{
    if (Index >= Unknown154)
        return -1;
    return Unknown15C[Index];
}
