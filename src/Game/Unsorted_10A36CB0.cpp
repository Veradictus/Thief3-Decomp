// Game/Unsorted_10A36CB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A36CF0
{
    char Unknown00[0x274];
    int Unknown274;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10A36CF0* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10A37700
{
public:
    void FUN_10a37700();

    char Unknown00[0x32C];
    unsigned char Unknown32C;
    char Unknown32D[0x257];
    unsigned char Unknown584;
    char Unknown585[3];
    int Unknown588;
};

// FUNCTION: 0x10A36CF0 ?FUN_10a36cf0@@YAXXZ
void FUN_10a36cf0()
{
    if (DAT_10f35dec->Unknown08)
    {
        DAT_10f35dec->Unknown08->Unknown274--;
        if (DAT_10f35dec->Unknown08->Unknown274 < 0)
            DAT_10f35dec->Unknown08->Unknown274 = 0;
    }
}

// FUNCTION: 0x10A37700 ?FUN_10a37700@Class_10A37700@@QAEXXZ
void Class_10A37700::FUN_10a37700()
{
    Unknown588--;
    if (Unknown588 < 0)
        Unknown588 = 0;
    if (Unknown584 != 0 && Unknown588 == 0)
        Unknown32C = 0;
}
