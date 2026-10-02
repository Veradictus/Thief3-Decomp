// Game/Unsorted_10AC44C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6F6A8 {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual bool FUN_10ac5c10();
    char Unknown04[0xcc];
    void* Unknownd0;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10AC4920
{
public:
    void FUN_10ac44c0(int Count);
    void FUN_10ac4920();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10AC4920 ?FUN_10ac4920@Class_10AC4920@@QAEXXZ
void Class_10AC4920::FUN_10ac4920()
{
    FUN_10ac44c0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10AC5C10 ?FUN_10ac5c10@Class_10E6F6A8@@UAE_NXZ
bool Class_10E6F6A8::FUN_10ac5c10()
{
    return Unknownd0 != 0;
}
