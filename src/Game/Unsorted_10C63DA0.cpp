// Game/Unsorted_10C63DA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10C63DA0
{
public:
    virtual void Virtual0();
    virtual bool Virtual1();

    char Unknown04[0x46];
    bool Unknown4A;
};

class Class_10C63DA0
{
public:
    void FUN_10c63da0(bool Value);

    char Unknown00[8];
    Object_10C63DA0* Unknown08;
};

// FUNCTION: 0x10C63DA0 ?FUN_10c63da0@Class_10C63DA0@@QAEX_N@Z
void Class_10C63DA0::FUN_10c63da0(bool Value)
{
    if (Unknown08->Virtual1())
        Unknown08->Unknown4A = Value;
}
