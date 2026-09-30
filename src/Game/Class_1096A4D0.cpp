// Game/Class_1096A4D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_1096A4D0
{
    char Unknown00[0x8C];
    unsigned char Unknown8C;
    char Unknown8D[0x1F];
    int UnknownAC;
};

struct Info_10F344EC
{
    char Unknown00[0x78];
    int Unknown78[1];
};

extern int DAT_10f344ec;

class Class_1096A4D0
{
public:
    int FUN_1096a4d0();

    int Unknown00;
    Info_1096A4D0* Unknown04;
};

// FUNCTION: 0x1096A4D0 ?FUN_1096a4d0@Class_1096A4D0@@QAEHXZ
int Class_1096A4D0::FUN_1096a4d0()
{
    int Max = Unknown04->UnknownAC - 1;
    int Value = ((Info_10F344EC*)DAT_10f344ec)->Unknown78[Unknown04->Unknown8C];
    if (Value > Max)
        return Max;
    return Value;
}
