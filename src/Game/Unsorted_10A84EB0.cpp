// Game/Unsorted_10A84EB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A854C0
{
public:
    virtual void Virtual0();
    virtual ~Class_10A854C0();
};

extern Class_10A854C0* DAT_10f3a198;

// FUNCTION: 0x10A854C0 ?FUN_10a854c0@@YAXXZ
void FUN_10a854c0()
{
    if (DAT_10f3a198)
    {
        delete DAT_10f3a198;
        DAT_10f3a198 = 0;
    }
}
