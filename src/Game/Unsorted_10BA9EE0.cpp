// Game/Unsorted_10BA9EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520
{
    char Unknown00[8];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10BA9EE0
{
public:
    int FUN_10ba9ee0();
};

// FUNCTION: 0x10BA9EE0 ?FUN_10ba9ee0@Class_10BA9EE0@@QAEHXZ
int Class_10BA9EE0::FUN_10ba9ee0()
{
    if (!DAT_10f35dec)
        return 0;
    return DAT_10f35dec->Unknown08;
}
