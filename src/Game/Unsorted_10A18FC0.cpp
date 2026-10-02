// Game/Unsorted_10A18FC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A18FC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int Virtual2();
};

class Class_10E6C484 : public Object_10A18FC0
{
public:
    Class_10E6C484();
    ~Class_10E6C484();
};

// FUNCTION: 0x10A18FC0 ?FUN_10a18fc0@@YAPAVObject_10A18FC0@@XZ
Object_10A18FC0* FUN_10a18fc0()
{
    static Class_10E6C484 Instance;
    return &Instance;
}
