// Game/Unsorted_10A88F80_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A89010_Unknown678
{
    char Unknown00[0x814];
    int Unknown814;
};

class Class_10E6C484
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10a89010();

    char Unknown04[0x674];
    Struct_10A89010_Unknown678* Unknown678;
};

// FUNCTION: 0x10A89010 ?FUN_10a89010@Class_10E6C484@@UAEHXZ
int Class_10E6C484::FUN_10a89010()
{
    if (!Unknown678)
        return 0;
    return Unknown678->Unknown814;
}
