// Game/Unsorted_10BA0220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA1270
{
public:
    virtual ~Class_10BA1270();
};

extern Class_10BA1270* DAT_10ff6680;

struct Struct_10BA12F0
{
    char Unknown00[0xC];
    int Count;
    char Unknown10[4];
    void** Items;
};

class Class_10BA12F0
{
public:
    void FUN_10ba12f0();

    void* Current;
    Struct_10BA12F0* Container;
    int Index;
};

// FUNCTION: 0x10BA1270 ?FUN_10ba1270@@YAXXZ
void FUN_10ba1270()
{
    if (DAT_10ff6680)
    {
        delete DAT_10ff6680;
        DAT_10ff6680 = 0;
    }
}

// FUNCTION: 0x10BA12F0 ?FUN_10ba12f0@Class_10BA12F0@@QAEXXZ
void Class_10BA12F0::FUN_10ba12f0()
{
    Index = -1;
    Current = 0;
    do {
        Index++;
        if (Index >= Container->Count) {
            Index = -1;
            return;
        }
        Current = Container->Items[Index];
    } while (Current == 0);
}
