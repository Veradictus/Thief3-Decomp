// Game/Unsorted_10BB7F30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

float appFrand();

class Class_10BB7F60
{
public:
    float FUN_10bb7f60();

    char Unknown00[0x29C];
    float Unknown29C;
};

class AAIPawn;

class Class_10B9CAC0;

struct Struct_10B9BCA0
{
    char Unknown00[8];
    Class_10B9CAC0* Unknown08;
};

class Class_10B9BCA0
{
public:
    char Unknown00[0x118];
    Struct_10B9BCA0* Unknown118;
};

Class_10B9BCA0* FUN_10baa660(AAIPawn* Pawn);

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

class Class_10BB7F30
{
public:
    Class_10B9CAC0* FUN_10bb7f30();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

// FUNCTION: 0x10BB7F30 ?FUN_10bb7f30@Class_10BB7F30@@QAEPAVClass_10B9CAC0@@XZ
Class_10B9CAC0* Class_10BB7F30::FUN_10bb7f30()
{
    Class_10B9BCA0* Controller = FUN_10baa660((AAIPawn*)Unknown08->FUN_10c7d570());
    if (Controller && Controller->Unknown118 && Controller->Unknown118->Unknown08)
        return Controller->Unknown118->Unknown08;
    return 0;
}

// FUNCTION: 0x10BB7F60 ?FUN_10bb7f60@Class_10BB7F60@@QAEMXZ
float Class_10BB7F60::FUN_10bb7f60()
{
    if (Unknown29C == DAT_10eafbdc)
        Unknown29C = appFrand();
    return Unknown29C;
}
