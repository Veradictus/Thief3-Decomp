// Game/Unsorted_10A51D70_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A51DB0
{
public:
    virtual ~Object_10A51DB0();
};

class Class_10E5B2C0
{
public:
    virtual void Virtual0();

    void FUN_10a51db0();

    char Unknown04[0x100];
    Object_10A51DB0* Unknown104;
};

// FUNCTION: 0x10A51DB0 ?FUN_10a51db0@Class_10E5B2C0@@QAEXXZ
void Class_10E5B2C0::FUN_10a51db0()
{
    delete Unknown104;
    Unknown104 = 0;
}
