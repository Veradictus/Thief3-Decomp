// Game/Unsorted_109E34B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E3750
{
public:
    char Unknown00[0xdc];
    void* FieldDC;
    void* FUN_109e3750();
};

class Class_109E3760
{
public:
    char Unknown00[0xe0];
    void* Field_E0;
    void* FUN_109e3760();
};

class Class_109E37D0
{
public:
    char Unknown00[0xcc];
    unsigned char FieldCC;
    unsigned char FUN_109e37d0();
};

class Class_109E37E0 {
    char Unknown00[0xcc];
    unsigned char FieldCC;
public:
    void FUN_109e37e0(unsigned char param);
};

class Class_109E37F0
{
public:
    char Unknown00[0xcd];
    unsigned char FieldCD;
    unsigned char FUN_109e37f0();
};

class Class_109E3800 {
    char Unknown00[0xcd];
    unsigned char FieldCD;
public:
    void FUN_109e3800(unsigned char param);
};

// FUNCTION: 0x109E3750 ?FUN_109e3750@Class_109E3750@@QAEPAXXZ
void* Class_109E3750::FUN_109e3750()
{
    return &FieldDC;
}

// FUNCTION: 0x109E3760 ?FUN_109e3760@Class_109E3760@@QAEPAXXZ
void* Class_109E3760::FUN_109e3760()
{
    return &Field_E0;
}

// FUNCTION: 0x109E37D0 ?FUN_109e37d0@Class_109E37D0@@QAEEXZ
unsigned char Class_109E37D0::FUN_109e37d0()
{
    return FieldCC;
}

// FUNCTION: 0x109E37E0 ?FUN_109e37e0@Class_109E37E0@@QAEXE@Z
void Class_109E37E0::FUN_109e37e0(unsigned char param)
{
    FieldCC = param;
}

// FUNCTION: 0x109E37F0 ?FUN_109e37f0@Class_109E37F0@@QAEEXZ
unsigned char Class_109E37F0::FUN_109e37f0()
{
    return FieldCD;
}

// FUNCTION: 0x109E3800 ?FUN_109e3800@Class_109E3800@@QAEXE@Z
void Class_109E3800::FUN_109e3800(unsigned char param)
{
    FieldCD = param;
}
