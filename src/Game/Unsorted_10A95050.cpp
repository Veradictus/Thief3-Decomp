// Game/Unsorted_10A95050.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAB5C0_Result
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int Virtual7(int p1);
};

class Class_10AAB5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    int FUN_10aab5c0();
};

class Class_10E6CE50 : public Class_10AAB5C0
{
public:
    virtual void FUN_10a958f0();

    char Unknown04[8];
    int Unknown0C;
};

// FUNCTION: 0x10A958F0 ?FUN_10a958f0@Class_10E6CE50@@UAEXXZ
void Class_10E6CE50::FUN_10a958f0()
{
    Unknown0C = ((Class_10AAB5C0_Result*)FUN_10aab5c0())->Virtual7(0);
}
