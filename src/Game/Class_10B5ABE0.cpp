// Game/Class_10B5ABE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Constructor-like initialization with vtable stores

extern void* DAT_10e828b0[];

extern void* DAT_10e7edb8[];

extern void FUN_10a58e50(void);

class Class_10B5ABE0 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b5abe0();
};

// FUNCTION: 0x10B5ABE0 ?FUN_10b5abe0@Class_10B5ABE0@@QAEXXZ
void Class_10B5ABE0::FUN_10b5abe0()
{
    *(void**)this = DAT_10e828b0;
    Field118 = DAT_10e7edb8;
    FUN_10a58e50();
}
