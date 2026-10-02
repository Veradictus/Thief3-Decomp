// Game/Unsorted_10A51D70_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A51D90
{
public:
    virtual ~Object_10A51D90();
};

class Class_10E5B2C0
{
public:
    virtual void Virtual0();

    void FUN_10a51d90();

    char Unknown04[0xFC];
    Object_10A51D90* Unknown100;
};

// FUNCTION: 0x10A51D90 ?FUN_10a51d90@Class_10E5B2C0@@QAEXXZ
void Class_10E5B2C0::FUN_10a51d90()
{
    delete Unknown100;
    Unknown100 = 0;
}
