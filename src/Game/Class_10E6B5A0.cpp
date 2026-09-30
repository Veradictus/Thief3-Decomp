// Game/Class_10E6B5A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4dd6c[];

extern void* DAT_10e6b5a0[];

extern int DAT_10f11380;

class Class_10E6B5A0
{
public:
    Class_10E6B5A0* FUN_10a68b30();

    void* VTable;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10A68B30 ?FUN_10a68b30@Class_10E6B5A0@@QAEPAV1@XZ
Class_10E6B5A0* Class_10E6B5A0::FUN_10a68b30()
{
    VTable = DAT_10e4dd6c;
    Unknown04 = 0x10;
    Unknown0C = 1;
    Unknown10 = DAT_10f11380++;
    VTable = DAT_10e6b5a0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    return this;
}
