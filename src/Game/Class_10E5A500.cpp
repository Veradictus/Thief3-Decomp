// Game/Class_10E5A500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void FUN_109dc040(void);

extern void* DAT_10e5a500[];

class Class_10E5A500
{
public:
    void* Vtable;
    char Unknown04[0x1314];
    int Unknown1318;
    int Unknown131C;

    Class_10E5A500* FUN_109dc1f0();
};

// FUNCTION: 0x109DC1F0 ?FUN_109dc1f0@Class_10E5A500@@QAEPAV1@XZ
Class_10E5A500* Class_10E5A500::FUN_109dc1f0()
{
    FUN_109dc040();
    Unknown1318 = 0;
    Unknown131C = 0;
    Vtable = DAT_10e5a500;
    return this;
}
