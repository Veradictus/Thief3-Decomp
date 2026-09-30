// Game/Class_10A69170.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef void (*VFunc)(void);

class Class_10A69170 {
public:
    void FUN_10a69170();
};

// FUNCTION: 0x10A69170 ?FUN_10a69170@Class_10A69170@@QAEXXZ
void Class_10A69170::FUN_10a69170()
{
    VFunc* vtable = (VFunc*)*(VFunc**)this;
    vtable[7]();
}
