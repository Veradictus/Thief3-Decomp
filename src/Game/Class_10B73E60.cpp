// Game/Class_10B73E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e876d0;

extern void* DAT_10e7edb8[];

extern void FUN_10a58e50(void);

class Class_10B73E60 {
public:
    char Unknown00[0x118];
    void* Field118;
    void FUN_10b73e60();
};

// FUNCTION: 0x10B73E60 ?FUN_10b73e60@Class_10B73E60@@QAEXXZ
void Class_10B73E60::FUN_10b73e60()
{
    *(void**)this = &DAT_10e876d0;
    Field118 = DAT_10e7edb8;
    FUN_10a58e50();
}
