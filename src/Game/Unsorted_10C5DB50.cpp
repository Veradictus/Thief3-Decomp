// Game/Unsorted_10C5DB50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9C9A8
{
public:
    Class_10E9C9A8();
    virtual ~Class_10E9C9A8();
    int Unknown04;
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

class Class_10C5EE80
{
public:
    void FUN_10c5e600(int Count);
    void FUN_10c5ee80();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10C5EE80 ?FUN_10c5ee80@Class_10C5EE80@@QAEXXZ
void Class_10C5EE80::FUN_10c5ee80()
{
    FUN_10c5e600(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C5F350 ??0Class_10E9C9A8@@QAE@XZ
Class_10E9C9A8::Class_10E9C9A8()
{
    Unknown04 = 0;
}

// FUNCTION: 0x10C5F3C0 ??_GClass_10E9C9A8@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10C5F350's definition in this unit.
