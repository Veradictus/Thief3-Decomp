// Game/Unsorted_10951EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10951EE0_Unknown17C
{
public:
    virtual void Virtual0();
};

extern int DAT_10f2c720;

class Class_10951EE0
{
public:
    Class_10951EE0_Unknown17C* FUN_10951ee0();

    char Unknown00[0x17C];
    Class_10951EE0_Unknown17C* Unknown17C[1];
};

// FUNCTION: 0x10951EE0 ?FUN_10951ee0@Class_10951EE0@@QAEPAVClass_10951EE0_Unknown17C@@XZ
Class_10951EE0_Unknown17C* Class_10951EE0::FUN_10951ee0()
{
    if (Unknown17C[DAT_10f2c720])
        Unknown17C[DAT_10f2c720]->Virtual0();
    return Unknown17C[DAT_10f2c720];
}
