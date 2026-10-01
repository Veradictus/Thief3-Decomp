// Game/Unsorted_10B251C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void* FUN_10b154c0();

class Class_10B16930
{
public:
    void FUN_10b16860(int A);
    void FUN_10b166a0();
};

class Class_10B25200
{
public:
    void FUN_10b251c0(int A);

    char Unknown00[0x28];
    int Unknown28;
    char Unknown2C[0x1C];
    int Unknown48;
    int Unknown4C;
};

// FUNCTION: 0x10B251C0 ?FUN_10b251c0@Class_10B25200@@QAEXH@Z
void Class_10B25200::FUN_10b251c0(int A)
{
    Unknown4C = A;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b16860(A);
    Unknown48 = Unknown28 = 3;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b166a0();
}
