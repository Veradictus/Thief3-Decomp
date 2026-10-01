// Game/Unsorted_10AB5B50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AB72D0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10AB72D0* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10AB72D0
{
public:
    void FUN_10ab72d0();
};

class Class_10E49AC4
{
public:
    Class_10E49AC4();

    virtual void Virtual0();

    void FUN_10ab6e50();

    char Unknown04[0x54];
    bool Unknown58;
    bool Unknown59;
    bool Unknown5A;
};

// FUNCTION: 0x10AB6EB0 ??0Class_10E49AC4@@QAE@XZ
Class_10E49AC4::Class_10E49AC4()
{
    Unknown58 = false;
    Unknown59 = false;
    Unknown5A = false;
    FUN_10ab6e50();
}

// FUNCTION: 0x10AB72D0 ?FUN_10ab72d0@Class_10AB72D0@@QAEXXZ
void Class_10AB72D0::FUN_10ab72d0()
{
    DAT_10f46da0->Virtual2(this);
}
