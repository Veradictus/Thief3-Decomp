// Game/Unsorted_10BBB8D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330;

class Class_10971570;

struct Struct_10BBD8B0
{
    char Unknown00[4];
    int Unknown04;
    float* Unknown08;
    bool* Unknown0C;
};

class Class_10BBDC30
{
public:
    bool FUN_10bbd840(int A);
    bool FUN_10bbd870(int A, float* B);
    bool FUN_10bbd8b0(int A, bool* B);
    float FUN_10bbdad0(int A);
    bool FUN_10bbdc30(int A);
    bool FUN_10bbdcc0(int A);

    char Unknown00[4];
    Class_1098E330* Unknown04;
    char Unknown08[4];
    Class_10971570* Unknown0C;
    char Unknown10[4];
    Class_10971570* Unknown14;
    int Unknown18;
    char Unknown1C[4];
    Struct_10BBD8B0** Unknown20;
};

// FUNCTION: 0x10BBD840 ?FUN_10bbd840@Class_10BBDC30@@QAE_NH@Z
bool Class_10BBDC30::FUN_10bbd840(int A)
{
    for (int i = 0; i < Unknown18; i++)
    {
        if (Unknown20[i]->Unknown04 == A)
            return true;
    }
    return false;
}
