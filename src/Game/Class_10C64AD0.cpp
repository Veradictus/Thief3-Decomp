// Game/Class_10C64AD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10ffc7a0;

extern void* DAT_10ffc7a4;

extern void* DAT_10f35f68;

class Class_10C64AD0
{
public:
    Class_10C64AD0* FUN_10c64ad0(void* Arg);

    void* Unknown00;
    int Unknown04;
    void* Unknown08;
    void* Unknown0C;
    void* Unknown10;
};

// FUNCTION: 0x10C64AD0 ?FUN_10c64ad0@Class_10C64AD0@@QAEPAV1@PAX@Z
Class_10C64AD0* Class_10C64AD0::FUN_10c64ad0(void* Arg)
{
    Unknown00 = Arg;
    Unknown08 = DAT_10ffc7a0;
    Unknown0C = DAT_10ffc7a4;
    Unknown10 = DAT_10f35f68;
    return this;
}
