// Game/Unsorted_10BB7E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

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

class Class_10BB7E60
{
public:
    bool FUN_10bb7e60();
    bool FUN_10bb7ea0();

    char Unknown00[8];
    Class_10DBD510* Unknown08;
    char Unknown0C[0x254];
    float Unknown260;
};

// FUNCTION: 0x10BB7E60 ?FUN_10bb7e60@Class_10BB7E60@@QAE_NXZ
bool Class_10BB7E60::FUN_10bb7e60()
{
    float Value = Unknown08->FUN_10dbd510(0x1004b6)->FUN_10bbdb40();
    if (Value > DAT_10eafbdc && Value < Unknown260)
        return true;
    return false;
}

// FUNCTION: 0x10BB7EA0 ?FUN_10bb7ea0@Class_10BB7E60@@QAE_NXZ
bool Class_10BB7E60::FUN_10bb7ea0()
{
    float Value = Unknown08->FUN_10dbd510(0x100838)->FUN_10bbdb40();
    if (Value > DAT_10eafbdc && Value < Unknown260)
        return true;
    return false;
}
