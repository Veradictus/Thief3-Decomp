// Game/Unsorted_10A98DF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5B578
{
public:
    virtual void Virtual0() = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* Listener, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6DC88_Primary
{
public:
    virtual void FUN_10ba38f0();

    char Unknown04[8];
};

class Class_10E6DC88 : public Class_10E6DC88_Primary, public Class_10E5B578
{
public:
    int Unknown10;
};

class Class_10E6D07C : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a99350();
};

class Class_10E6D098 : public Class_10E6DC88
{
public:
    virtual void Virtual1();
    virtual void FUN_10a99420();
};

// FUNCTION: 0x10A99350 ?FUN_10a99350@Class_10E6D07C@@UAEXXZ
void Class_10E6D07C::FUN_10a99350()
{
    DAT_10f46da0->Virtual1(this, 0x7a, -1, -1);
}

// FUNCTION: 0x10A99420 ?FUN_10a99420@Class_10E6D098@@UAEXXZ
void Class_10E6D098::FUN_10a99420()
{
    DAT_10f46da0->Virtual1(this, 0x79, -1, -1);
}
