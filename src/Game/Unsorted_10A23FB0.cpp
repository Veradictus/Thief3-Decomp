// Game/Unsorted_10A23FB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A242D0 {
public:
    int FUN_10a242d0();
    char Unknown00[0x8];
    int Field08;
};

void FUN_10a2b520();

class Class_10A2EE50
{
public:
    Class_10A2EE50* FUN_10a2ee50();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

void FUN_10a2f7a0();

class Class_10A311E0;
extern Class_10A311E0* DAT_10f39f3c;

class Class_10A33EC0
{
public:
    char Unknown00[0x3c];
    unsigned char Field3c;
public:
    void FUN_10a33ec0();
};

class Class_10A33ED0
{
public:
    char Unknown00[0x3c];
    unsigned char Field3c;
public:
    void FUN_10a33ed0();
};

// FUNCTION: 0x10A242D0 ?FUN_10a242d0@Class_10A242D0@@QAEHXZ
int Class_10A242D0::FUN_10a242d0()
{
    return Field08 + 1;
}

// FUNCTION: 0x10A2C060 ?FUN_10a2c060@@YAXXZ
void FUN_10a2c060()
{
    FUN_10a2b520();
}

// FUNCTION: 0x10A2EE50 ?FUN_10a2ee50@Class_10A2EE50@@QAEPAV1@XZ
Class_10A2EE50* Class_10A2EE50::FUN_10a2ee50()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = -1;
    return this;
}

// FUNCTION: 0x10A2FC00 ?FUN_10a2fc00@@YAXXZ
void FUN_10a2fc00()
{
    FUN_10a2f7a0();
}

// FUNCTION: 0x10A30E50 ?FUN_10a30e50@@YAPAXXZ
void* FUN_10a30e50()
{
    return DAT_10f39f3c;
}

// FUNCTION: 0x10A33EC0 ?FUN_10a33ec0@Class_10A33EC0@@QAEXXZ
void Class_10A33EC0::FUN_10a33ec0()
{
    Field3c = 1;
}

// FUNCTION: 0x10A33ED0 ?FUN_10a33ed0@Class_10A33ED0@@QAEXXZ
void Class_10A33ED0::FUN_10a33ed0()
{
    Field3c = 0;
}
