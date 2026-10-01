// Game/Unsorted_10C63EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C63EE0_Field08
{
    char Unknown00[0x40];
    int Unknown40;
};

class Class_10C63EE0
{
public:
    char Unknown00[8];
    Struct_10C63EE0_Field08* Unknown08;
    int FUN_10c63ee0();
};

struct Elem_10C64AC0
{
    char Unknown00[0x38];
};

class Class_10c64ac0
{
public:
    char Unknown00[0x1c];
    Elem_10C64AC0 Unknown1C[1];

    Elem_10C64AC0* FUN_10c64ac0(int Index);
};

// FUNCTION: 0x10C63EE0 ?FUN_10c63ee0@Class_10C63EE0@@QAEHXZ
int Class_10C63EE0::FUN_10c63ee0()
{
    return Unknown08->Unknown40;
}

// FUNCTION: 0x10C64AC0 ?FUN_10c64ac0@Class_10c64ac0@@QAEPAUElem_10C64AC0@@H@Z
Elem_10C64AC0* Class_10c64ac0::FUN_10c64ac0(int Index)
{
    return &Unknown1C[Index];
}
