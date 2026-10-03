// Game/Unsorted_10ACB320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E50610
{
public:
    virtual ~Class_10E50610() {}
};

class Class_10E5D360 : public Class_10E50610
{
public:
    Class_10E5D360(int Value) : Unknown04(Value) {}

    virtual void Virtual1();
    virtual int FUN_10b9caa0(Class_10E5D360* Other);

    int Unknown04;
};

class Class_10E6FF90;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E6FF90* Obj, int B, int C, Class_10E5D360* D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6FF90
{
public:
    Class_10E6FF90();

    virtual void FUN_10c13ea0(int A, int B, int C, int D);
};

// FUNCTION: 0x10ACB320 ??0Class_10E6FF90@@QAE@XZ
Class_10E6FF90::Class_10E6FF90()
{
    Class_10E5D360 Local(0x20003c2);
    DAT_10f46da0->Virtual1(this, 1, -1, &Local);
}
