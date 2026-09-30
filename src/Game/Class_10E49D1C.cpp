// Game/Class_10E49D1C.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e49d1c[];

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49D1C
{
public:
    void FUN_10932ed0();

    void* VTable;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
};

// FUNCTION: 0x10932ED0 ?FUN_10932ed0@Class_10E49D1C@@QAEXXZ
void Class_10E49D1C::FUN_10932ed0()
{
    VTable = DAT_10e49d1c;
    Unknown04 = 0;
    Unknown08 = -1;
    memset(&Unknown10, 0, sizeof(Unknown10));
    Unknown0C = 0;
}
