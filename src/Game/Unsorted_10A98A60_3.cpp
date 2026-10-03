// Game/Unsorted_10A98A60_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E662C0
{
public:
    virtual ~Class_10E662C0() {}
};

class Class_10E682E0 : public Class_10E662C0
{
public:
    Class_10E682E0(int Value) : Unknown04(Value) {}

    virtual Class_10E682E0* FUN_10a54ce0();

    int Unknown04;
};

class Class_10E5B578
{
public:
    virtual void FUN_10bbe970() = 0;
};

class Class_10EB766C
{
public:
    virtual void Virtual0();

    int Unknown04;
    int Unknown08;
};

class Class_10E6DC88 : public Class_10EB766C, public Class_10E5B578
{
public:
    int Unknown10;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, Class_10E682E0* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6CFD4 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a98ac0();
};

// FUNCTION: 0x10A98AC0 ?FUN_10a98ac0@Class_10E6CFD4@@UAEXXZ
void Class_10E6CFD4::FUN_10a98ac0()
{
    Class_10E682E0 Local(1);
    DAT_10f46da0->Virtual1(this, 0x77, -1, &Local);
}
