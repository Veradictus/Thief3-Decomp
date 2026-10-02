// Game/Unsorted_10A986D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6CF9C : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a98770();
};

// FUNCTION: 0x10A98770 ?FUN_10a98770@Class_10E6CF9C@@UAEXXZ
void Class_10E6CF9C::FUN_10a98770()
{
    DAT_10f46da0->Virtual1(this, 0x7c, -1, -1);
}
