// Game/Unsorted_10A88F80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A88FF0
{
    char Unknown00[0x818];
    int Unknown818;
};

class Class_10E6C484
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a88ff0();

    char Unknown04[0x674];
    Struct_10A88FF0* Unknown678;
};

// FUNCTION: 0x10A88FF0 ?FUN_10a88ff0@Class_10E6C484@@UAEHXZ
int Class_10E6C484::FUN_10a88ff0()
{
    if (Unknown678 == 0)
        return 0;
    return Unknown678->Unknown818;
}
