// Game/Unsorted_10BB81B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10BB8210
{
public:
    int FUN_10bb8210();

    char Unknown00[0x2BC];
    float Unknown2BC;
};

float appFrand();

class Class_10BBDB40
{
public:
    float FUN_10bbdb40();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

class Class_10BB81B0
{
public:
    void FUN_10bb81b0();

    char Unknown00[8];
    Class_10DBD510* Unknown08;
    char Unknown0C[0x2B0];
    float Unknown2BC;
};

// FUNCTION: 0x10BB81B0 ?FUN_10bb81b0@Class_10BB81B0@@QAEXXZ
void Class_10BB81B0::FUN_10bb81b0()
{
    float Min = Unknown08->FUN_10dbd510(0x1006df)->FUN_10bbdb40();
    float Max = Unknown08->FUN_10dbd510(0x1006e0)->FUN_10bbdb40();
    Unknown2BC = Min + (Max - Min) * appFrand();
}

// FUNCTION: 0x10BB8210 ?FUN_10bb8210@Class_10BB8210@@QAEHXZ
int Class_10BB8210::FUN_10bb8210()
{
    if (Unknown2BC <= DAT_10eafbdc)
        return 1;
    return 0;
}
