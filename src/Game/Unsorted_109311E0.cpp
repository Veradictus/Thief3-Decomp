// Game/Unsorted_109311E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e49d1c[];

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49D1C
{
public:
    void FUN_10932ed0();

    void* VTable;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
};

class Class_109333a0
{
public:
    char Unknown00[0x10];
    int Field10;
    char Unknown14[0x24];
    int Field38;
    int FUN_109333a0();
};

extern int DAT_10f31bdc;

class Class_10939570;
extern Class_10939570* DAT_10f323fc;

extern int DAT_10f340ac;

extern int DAT_10f340c0;

// FUNCTION: 0x10932ED0 ?FUN_10932ed0@Class_10E49D1C@@QAEXXZ
void Class_10E49D1C::FUN_10932ed0()
{
    VTable = DAT_10e49d1c;
    Unknown04 = 0;
    Unknown08 = -1;
    memset(&Unknown10, 0, sizeof(Unknown10));
    Unknown0C = 0;
}

// FUNCTION: 0x109333A0 ?FUN_109333a0@Class_109333a0@@QAEHXZ
int Class_109333a0::FUN_109333a0()
{
    return Field10 - Field38;
}

// FUNCTION: 0x10934DD0 ?FUN_10934dd0@@YAHXZ
int FUN_10934dd0()
{
    return 0x80;
}

// FUNCTION: 0x10937510 ?FUN_10937510@@YAXXZ
void FUN_10937510()
{
    DAT_10f31bdc = 0;
}

// FUNCTION: 0x10939370 ?FUN_10939370@@YAXXZ
void FUN_10939370()
{
    DAT_10f323fc = 0;
}

// FUNCTION: 0x1093E920 ?FUN_1093e920@@YAXXZ
void FUN_1093e920()
{
    DAT_10f340ac = 0;
}

// FUNCTION: 0x1093EDA0 ?FUN_1093eda0@@YAXXZ
void FUN_1093eda0()
{
    DAT_10f340c0 = 0;
}
