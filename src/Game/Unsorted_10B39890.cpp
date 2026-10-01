// Game/Unsorted_10B39890.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int Index);

    char Unknown00[0xC];
    char Unknown0C[0x10];
    int Unknown1C;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B39890
{
public:
    void* FUN_10b39890(int A);
};

// FUNCTION: 0x10B39890 ?FUN_10b39890@Class_10B39890@@QAEPAXH@Z
void* Class_10B39890::FUN_10b39890(int A)
{
    return FUN_10b3abf0()->FUN_10b3a460(A)->Unknown0C;
}
