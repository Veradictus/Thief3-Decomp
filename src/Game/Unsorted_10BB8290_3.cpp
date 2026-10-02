// Game/Unsorted_10BB8290_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10A2C2F0
{
public:
    bool FUN_10a2c530(void* A, int* B, int C);
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB82C0
{
public:
    bool FUN_10bb82c0(int A);

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

// FUNCTION: 0x10BB82C0 ?FUN_10bb82c0@Class_10BB82C0@@QAE_NH@Z
bool Class_10BB82C0::FUN_10bb82c0(int A)
{
    if (Unknown284)
        return FUN_10a2c6b0()->FUN_10a2c530(Unknown08->FUN_10c7d570(), &Unknown284, A);
    return false;
}
