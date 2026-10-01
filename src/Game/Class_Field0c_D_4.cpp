// Game/Class_Field0c_D_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AD20
{
public:
    float FUN_10b7ad20(int A);
};

extern float DAT_10e499a4;

class Class_Field0c_D
{
public:
    int FUN_10b47020(int A);
    float FUN_10b471c0(int A, int B);

    char Unknown00[8];
    Class_10B7AD20* Unknown08[2];
};

// FUNCTION: 0x10B471C0 ?FUN_10b471c0@Class_Field0c_D@@QAEMHH@Z
float Class_Field0c_D::FUN_10b471c0(int A, int B)
{
    int Index = FUN_10b47020(A);
    if (Index >= 0)
        return Unknown08[Index]->FUN_10b7ad20(B);
    return DAT_10e499a4;
}
