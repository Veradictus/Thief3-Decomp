// Game/Class_10B65DE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Constructor-like initialization with mixed vtable stores

extern void* DAT_10e68d80;

extern void* DAT_10e7edb8[];

extern void FUN_10a58e50(void);

class Class_10B65DE0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b65de0();
};

// FUNCTION: 0x10B65DE0 ?FUN_10b65de0@Class_10B65DE0@@QAEXXZ
void Class_10B65DE0::FUN_10b65de0()
{
    *(void**)this = &DAT_10e68d80;
    Field118 = DAT_10e7edb8;
    FUN_10a58e50();
}
