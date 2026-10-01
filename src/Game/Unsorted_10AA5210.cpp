// Game/Unsorted_10AA5210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA52C0
{
public:
    void FUN_10aa5240();
    void FUN_10aa5250(int p1);
    void FUN_10aa52c0();
};

class Class_10E6D600
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10aa5360(int A);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

// FUNCTION: 0x10AA52C0 ?FUN_10aa52c0@Class_10AA52C0@@QAEXXZ
void Class_10AA52C0::FUN_10aa52c0()
{
    FUN_10aa5250(0);
    FUN_10aa5240();
}

// FUNCTION: 0x10AA5360 ?FUN_10aa5360@Class_10E6D600@@UAEXH@Z
void Class_10E6D600::FUN_10aa5360(int A)
{
    Unknown04 = (Unknown04 + A) % Unknown08;
    Unknown0C -= A;
}
