// Game/Unsorted_109516E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_Pair0
{
    Struct_Pair0() : A(0), B(0) {}

    int A;
    int B;
};

struct Struct_Zero5
{
    Struct_Zero5() : A(0), B(0), C(0), D(0), E(0) {}

    int A;
    int B;
    int C;
    int D;
    int E;
};

struct Struct_One4
{
    Struct_One4() : A(1.0f), B(1.0f), C(1.0f), D(1.0f) {}

    float A;
    float B;
    float C;
    float D;
};

struct Struct_Zero4
{
    Struct_Zero4() : A(0), B(0), C(0), D(0) {}

    int A;
    int B;
    int C;
    int D;
};

struct Struct_One2
{
    Struct_One2() : A(1.0f), B(1.0f) {}

    float A;
    float B;
};

class Class_10E4AC6C
{
public:
    Class_10E4AC6C();

    virtual ~Class_10E4AC6C();

    int Unknown04;
    int Unknown08;
    float Unknown0C;
    float Unknown10;
    float Unknown14;
    float Unknown18;
    float Unknown1C;
    Struct_Pair0 Unknown20;
    int Unknown28;
    float Unknown2C;
    float Unknown30;
    float Unknown34;
    float Unknown38;
    int Unknown3C;
    Struct_Zero5 Unknown40;
    Struct_One4 Unknown54;
    Struct_Zero4 Unknown64;
    Struct_One2 Unknown74;
    Struct_Zero4 Unknown7C;
};

class Class_10939570
{
public:
    void* FUN_1093bd40(int* A, int B, int C);
};

extern Class_10939570* DAT_10f323fc;

class Class_10951900
{
public:
    void FUN_10951660();
    void FUN_10951900(int* A, int B);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[0x18];
    void* Unknown20;
    char Unknown24[4];
    int Unknown28;
};

// FUNCTION: 0x10951780 ??0Class_10E4AC6C@@QAE@XZ
Class_10E4AC6C::Class_10E4AC6C() : Unknown04(0)
{
    Unknown0C = 1.0f;
    Unknown10 = 1.0f;
    Unknown14 = 1.0f;
    Unknown18 = 1.0f;
    Unknown2C = 1.0f;
    Unknown30 = 1.0f;
    Unknown34 = 1.0f;
    Unknown38 = 1.0f;
    Unknown1C = 1.0f;
    Unknown28 = 0;
    Unknown3C = 0;
}

// FUNCTION: 0x10951900 ?FUN_10951900@Class_10951900@@QAEXPAHH@Z
void Class_10951900::FUN_10951900(int* A, int B)
{
    FUN_10951660();
    Unknown28 = B;
    if (B)
    {
        Unknown20 = DAT_10f323fc->FUN_1093bd40(A, 0, 0);
        if (!Unknown20)
            Unknown28 = 0;
        else if (Unknown28 == 1)
            Unknown04 |= 0x400;
    }
}

// FUNCTION: 0x10951A60 ??_GClass_10E4AC6C@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10951780's definition in this unit.
