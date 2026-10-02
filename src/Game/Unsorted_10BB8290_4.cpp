// Game/Unsorted_10BB8290_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10A2C2F0
{
public:
    void FUN_10a2c2a0(void* A, int* B);
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB8300
{
public:
    void FUN_10bb8300();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

// FUNCTION: 0x10BB8300 ?FUN_10bb8300@Class_10BB8300@@QAEXXZ
void Class_10BB8300::FUN_10bb8300()
{
    if (Unknown284)
    {
        FUN_10a2c6b0()->FUN_10a2c2a0(Unknown08->FUN_10c7d570(), &Unknown284);
        Unknown284 = 0;
    }
}
