// Game/Unsorted_10A30B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A30530
{
public:
    void FUN_10a30530(int Count);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A30690;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10A30690* A);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E663B4;

extern Class_10E663B4* DAT_10f39f38;

class Class_10A30690
{
public:
    ~Class_10A30690();

    void FUN_10a30e10();

    int Unknown00;
    Class_10A30530 Unknown04;
    bool Unknown10;
};

// FUNCTION: 0x10A30E10 ?FUN_10a30e10@Class_10A30690@@QAEXXZ
void Class_10A30690::FUN_10a30e10()
{
    if (Unknown10)
    {
        Unknown04.FUN_10a30530(0);
        DAT_10f46da0->Virtual2(this);
        Unknown10 = false;
        delete this;
        DAT_10f39f38 = 0;
    }
}
