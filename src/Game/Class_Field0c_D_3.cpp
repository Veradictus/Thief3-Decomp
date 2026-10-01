// Game/Class_Field0c_D_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AC30
{
public:
    float FUN_10b7ac30();
};

extern float DAT_10e499a4;

class Class_Field0c_D
{
public:
    int FUN_10b47020(int A);
    float FUN_10b47100(int A);

    char Unknown00[8];
    Class_10B7AC30* Unknown08[2];
};

// FUNCTION: 0x10B47100 ?FUN_10b47100@Class_Field0c_D@@QAEMH@Z
float Class_Field0c_D::FUN_10b47100(int A)
{
    int Index = FUN_10b47020(A);
    if (Index >= 0)
        return Unknown08[Index]->FUN_10b7ac30();
    return DAT_10e499a4;
}
