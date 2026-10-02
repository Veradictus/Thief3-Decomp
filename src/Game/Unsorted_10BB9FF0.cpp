// Game/Unsorted_10BB9FF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10A2C2F0
{
public:
    void FUN_10a2c250(void* A, int* B);
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB9FC0
{
public:
    void FUN_10bb9e90();
    void FUN_10bb9ff0();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

// FUNCTION: 0x10BB9FF0 ?FUN_10bb9ff0@Class_10BB9FC0@@QAEXXZ
void Class_10BB9FC0::FUN_10bb9ff0()
{
    FUN_10bb9e90();
    if (Unknown284)
        FUN_10a2c6b0()->FUN_10a2c250(Unknown08->FUN_10c7d570(), &Unknown284);
}
