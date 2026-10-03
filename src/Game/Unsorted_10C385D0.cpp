// Game/Unsorted_10C385D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C80360
{
public:
    unsigned char FUN_10c80360();
};

class Class_10C099A0
{
public:
    int FUN_10c099a0(int Value);
    bool FUN_10c099d0(int A);
};

class Class_10FF667C
{
public:
    char Unknown00[0x1C];
    Class_10C099A0* Unknown1C;
};

extern Class_10FF667C* DAT_10ff667c;

// FUNCTION: 0x10C385D0 ?FUN_10c385d0@@YG_NPAVClass_10C80360@@@Z
bool __stdcall FUN_10c385d0(Class_10C80360* A)
{
    if (A && (A->FUN_10c80360() & 8))
    {
        int Result = DAT_10ff667c->Unknown1C->FUN_10c099a0((int)A);
        if (Result)
            return DAT_10ff667c->Unknown1C->FUN_10c099d0(Result);
    }
    return false;
}
