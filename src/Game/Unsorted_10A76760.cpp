// Game/Unsorted_10A76760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10ad1dc0(void* Memory);

extern void* DAT_10e6bd64[];

extern void* DAT_10e6bd60[];

class Class_10A79670
{
public:
    void FUN_10a79670();

    void* VTable;
    char Unknown04[0x14];
    void* Unknown18;
};

extern void* DAT_10e6bd68[];

class Class_10E6BD68
{
public:
    Class_10E6BD68* FUN_10a796a0();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
};

// FUNCTION: 0x10A79670 ?FUN_10a79670@Class_10A79670@@QAEXXZ
void Class_10A79670::FUN_10a79670()
{
    VTable = DAT_10e6bd64;
    if (Unknown18)
        FUN_10ad1dc0(Unknown18);
    Unknown18 = 0;
    VTable = DAT_10e6bd60;
}

// FUNCTION: 0x10A796A0 ?FUN_10a796a0@Class_10E6BD68@@QAEPAV1@XZ
Class_10E6BD68* Class_10E6BD68::FUN_10a796a0()
{
    Unknown00 = DAT_10e6bd68;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    Unknown2C = 0;
    Unknown30 = 0;
    return this;
}
