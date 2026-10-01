// Game/Unsorted_10C1F990.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C20BC0 {
public:
    char Unknown00[0x3C];
    int Unknown3C;
    char Unknown40[0x30];
    unsigned char Unknown70;
    unsigned char Unknown71;
    unsigned char Unknown72;

    void FUN_10c20bc0();
};

struct Struct_10C20010
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C20010
{
public:
    Struct_10C20010 FUN_10c20010();

    Struct_10C20010 Unknown00;
};

struct Struct_10C20030
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C20030
{
public:
    Struct_10C20030 FUN_10c20030();

    char Unknown00[0xC];
    Struct_10C20030 Unknown0C;
};

// FUNCTION: 0x10C20010 ?FUN_10c20010@Class_10C20010@@QAE?AUStruct_10C20010@@XZ
Struct_10C20010 Class_10C20010::FUN_10c20010()
{
    return Unknown00;
}

// FUNCTION: 0x10C20030 ?FUN_10c20030@Class_10C20030@@QAE?AUStruct_10C20030@@XZ
Struct_10C20030 Class_10C20030::FUN_10c20030()
{
    return Unknown0C;
}

// FUNCTION: 0x10C20BC0 ?FUN_10c20bc0@Class_10C20BC0@@QAEXXZ
void Class_10C20BC0::FUN_10c20bc0()
{
    Unknown70 = 0;
    Unknown71 = 0;
    Unknown72 = 0;
    Unknown3C = 0;
}
