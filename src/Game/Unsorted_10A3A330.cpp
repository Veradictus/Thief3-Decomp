// Game/Unsorted_10A3A330.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A3A380;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10A3A380* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10A3A380_Primary
{
public:
    virtual void Virtual0();
};

class Class_10E667AC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10a3a380();
};

class Class_10A3A380 : public Class_10A3A380_Primary, public Class_10E667AC
{
public:
    virtual void FUN_10a3a380();
};

// FUNCTION: 0x10A3A380 ?FUN_10a3a380@Class_10A3A380@@UAEXXZ
void Class_10A3A380::FUN_10a3a380()
{
    DAT_10f46da0->Virtual2(this);
}
