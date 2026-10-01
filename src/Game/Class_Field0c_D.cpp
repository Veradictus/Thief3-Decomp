// Game/Class_Field0c_D.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AC10
{
public:
    float FUN_10b7ac10();
};

extern float DAT_10eafbdc;

class Class_Field0c_D
{
public:
    int FUN_10b47020(int A);
    float FUN_10b471f0(int A);

    char Unknown00[8];
    Class_10B7AC10* Unknown08[2];
};

// FUNCTION: 0x10B471F0 ?FUN_10b471f0@Class_Field0c_D@@QAEMH@Z
float Class_Field0c_D::FUN_10b471f0(int A)
{
    int Index = FUN_10b47020(A);
    if (Index >= 0)
        return Unknown08[Index]->FUN_10b7ac10();
    return DAT_10eafbdc;
}
