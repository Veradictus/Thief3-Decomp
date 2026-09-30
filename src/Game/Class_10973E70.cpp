// Game/Class_10973E70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10973E70 : public Class_10E70A50
{
public:
    void FUN_10973e70();

    char Unknown2C[0x58];
    int Field84;
};

// FUNCTION: 0x10973E70 ?FUN_10973e70@Class_10973E70@@QAEXXZ
void Class_10973E70::FUN_10973e70()
{
    Field84 = 0;
    Class_10E70A50::FUN_10adb3a0();
}
