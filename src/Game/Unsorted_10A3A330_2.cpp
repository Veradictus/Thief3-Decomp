// Game/Unsorted_10A3A330_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A3A330;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10A3A330* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10A3A330_Primary
{
public:
    virtual void Virtual0();
};

class Class_10E667AC
{
public:
    virtual void Virtual0();
    virtual void FUN_10a3ac50(int A);
    virtual void FUN_10a3a330();
    virtual void FUN_10a3a380();
};

class Class_10A3A330 : public Class_10A3A330_Primary, public Class_10E667AC
{
public:
    virtual void FUN_10a3a330();
};

// FUNCTION: 0x10A3A330 ?FUN_10a3a330@Class_10A3A330@@UAEXXZ
void Class_10A3A330::FUN_10a3a330()
{
    DAT_10f46da0->Virtual1(this, 0x3b, -1, -1);
    DAT_10f46da0->Virtual1(this, 0x27, -1, -1);
    DAT_10f46da0->Virtual1(this, 0x26, -1, -1);
    DAT_10f46da0->Virtual1(this, 6, -1, -1);
}
