// Game/Unsorted_10C28BD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C28CA0
{
public:
    ~Class_10C28CA0();

    char Unknown00[0xC];
    int Unknown0C;
};

extern Class_10C28CA0* DAT_10ff70a0;

// FUNCTION: 0x10C28D90 ?FUN_10c28d90@@YAXXZ
void FUN_10c28d90()
{
    --DAT_10ff70a0->Unknown0C;
    if (DAT_10ff70a0->Unknown0C == 0)
    {
        delete DAT_10ff70a0;
        DAT_10ff70a0 = 0;
    }
}
