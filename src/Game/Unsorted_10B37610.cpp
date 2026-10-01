// Game/Unsorted_10B37610.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ACF3A0
{
public:
    int FUN_10acf3a0(int A);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xFC];
    Class_10ACF3A0* UnknownFC;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10B22C40
{
public:
    void FUN_10b22c40(int A);
};

struct Struct_10B37610
{
    char Unknown00[0x458];
    int Unknown458;
};

class Class_10B37610
{
public:
    void FUN_10b37610(int A, int B, int C);

    char Unknown00[4];
    Struct_10B37610* Unknown04;
    Class_10B22C40* Unknown08;
};

// FUNCTION: 0x10B37610 ?FUN_10b37610@Class_10B37610@@QAEXHHH@Z
void Class_10B37610::FUN_10b37610(int A, int B, int C)
{
    Unknown04->Unknown458 = DAT_10f3a3d8->UnknownFC->FUN_10acf3a0(A);
    Unknown08->FUN_10b22c40(A);
}
