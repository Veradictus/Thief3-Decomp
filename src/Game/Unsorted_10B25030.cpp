// Game/Unsorted_10B25030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B251A0
{
public:
    int FUN_10b25080();
    void FUN_10b251a0();

    char Unknown00[0x2C];
    int Unknown2C;
};

class Class_10B251B0
{
public:
    int FUN_10b25100();
    void FUN_10b251b0();

    char Unknown00[0x2C];
    int Unknown2C;
};

struct Struct_10B25010
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B25010_Member
{
public:
    Struct_10B25010& operator[](int Index) { return Unknown08[Index]; }

    char Unknown00[8];
    Struct_10B25010* Unknown08;
};

class Class_10B1B8A0
{
public:
    char Unknown00[0x1C];
    Class_10B25010_Member Unknown1C;
};

Class_10B1B8A0* FUN_10b1b600();

class Class_10B255F0
{
public:
    int FUN_10b25030();

    char Unknown00[0x2C];
    int Unknown2C;
};

// FUNCTION: 0x10B25030 ?FUN_10b25030@Class_10B255F0@@QAEHXZ
int Class_10B255F0::FUN_10b25030()
{
    if (Unknown2C == 0)
        return 0;
    int Result = 0;
    if (FUN_10b1b600()->Unknown1C[Unknown2C].Unknown00)
        Result = FUN_10b1b600()->Unknown1C[Unknown2C].Unknown00;
    return Result;
}

// FUNCTION: 0x10B251A0 ?FUN_10b251a0@Class_10B251A0@@QAEXXZ
void Class_10B251A0::FUN_10b251a0()
{
    Unknown2C = FUN_10b25080();
}

// FUNCTION: 0x10B251B0 ?FUN_10b251b0@Class_10B251B0@@QAEXXZ
void Class_10B251B0::FUN_10b251b0()
{
    Unknown2C = FUN_10b25100();
}
