// Game/Unsorted_10C53200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9bea8[];

class Class_10E9BEA8
{
public:
    Class_10E9BEA8() { VTable = DAT_10e9bea8; }

    void** VTable;
};

extern Class_10E9BEA8* DAT_10ff70c8;

// FUNCTION: 0x10C53200 ?FUN_10c53200@@YAXXZ
void FUN_10c53200()
{
    if (DAT_10ff70c8 == 0)
        DAT_10ff70c8 = new Class_10E9BEA8;
}
