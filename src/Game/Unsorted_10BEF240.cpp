// Game/Unsorted_10BEF240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

float appFrand();

class Class_10BBDB40
{
public:
    float FUN_10bbdc80();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10BF0360
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BF0360
{
public:
    float FUN_10bef550();

    char Unknown00[4];
    Struct_10BF0360* Unknown04;
};

struct Struct_10BEF5B0
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BEF5B0
{
public:
    float FUN_10bef5b0();

    char Unknown00[4];
    Struct_10BEF5B0* Unknown04;
};

// FUNCTION: 0x10BEF550 ?FUN_10bef550@Class_10BF0360@@QAEMXZ
float Class_10BF0360::FUN_10bef550()
{
    float Min = Unknown04->Unknown08->FUN_10dbd510(0x100645)->FUN_10bbdc80();
    float Max = Unknown04->Unknown08->FUN_10dbd510(0x100646)->FUN_10bbdc80();
    return Min + (Max - Min) * appFrand();
}

// FUNCTION: 0x10BEF5B0 ?FUN_10bef5b0@Class_10BEF5B0@@QAEMXZ
float Class_10BEF5B0::FUN_10bef5b0()
{
    float Min = Unknown04->Unknown08->FUN_10dbd510(0x100643)->FUN_10bbdc80();
    float Max = Unknown04->Unknown08->FUN_10dbd510(0x100644)->FUN_10bbdc80();
    return Min + (Max - Min) * appFrand();
}
