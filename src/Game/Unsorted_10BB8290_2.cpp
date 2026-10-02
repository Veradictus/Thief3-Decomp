// Game/Unsorted_10BB8290_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A2C2F0
{
public:
    bool FUN_10a2c500(void* A, void* B);
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

Class_10A2C2F0* FUN_10a2c6b0();

class Class_10BB8290
{
public:
    bool FUN_10bb8290();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
    char Unknown0C[0x278];
    int Unknown284;
};

// FUNCTION: 0x10BB8290 ?FUN_10bb8290@Class_10BB8290@@QAE_NXZ
bool Class_10BB8290::FUN_10bb8290()
{
    if (Unknown284 == 0)
        return false;
    return FUN_10a2c6b0()->FUN_10a2c500(Unknown08->FUN_10c7d570(), &Unknown284);
}
