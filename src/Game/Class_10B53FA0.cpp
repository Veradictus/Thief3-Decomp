// Game/Class_10B53FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e81740[];

extern void* DAT_10e7edb8[];

extern void FUN_10a51620(void);

class Class_10B53FA0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b53fa0();
};

// FUNCTION: 0x10B53FA0 ?FUN_10b53fa0@Class_10B53FA0@@QAEXXZ
void Class_10B53FA0::FUN_10b53fa0()
{
    *(void**)this = DAT_10e81740;
    Field118 = DAT_10e7edb8;
    FUN_10a51620();
}
