// Game/Unsorted_10BBB8D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10971570
{
public:
    void FUN_10971570(int A, bool* B);
};

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

struct Struct_10BBD8B0
{
    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    bool* Unknown0C;
};

class Class_10BBDC30
{
public:
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

// FUNCTION: 0x10BBD8B0 ?FUN_10bbd8b0@Class_10BBDC30@@QAE_NHPA_N@Z
bool Class_10BBDC30::FUN_10bbd8b0(int A, bool* B)
{
    for (int i = 0; i < Unknown18; i++)
    {
        Struct_10BBD8B0* Entry = Unknown20[i];
        if (Entry->Unknown04 == A)
        {
            bool* Value = Entry->Unknown0C;
            if (!Value)
                return false;
            *B = *Value;
            return true;
        }
    }
    return false;
}

// FUNCTION: 0x10BBDAD0 ?FUN_10bbdad0@Class_10BBDC30@@QAEMH@Z
float Class_10BBDC30::FUN_10bbdad0(int A)
{
    float Result = 0.0f;
    if (FUN_10bbd870(A, &Result) != true)
        Unknown04->FUN_1098e330(A, (int*)&Result);
    return Result;
}
