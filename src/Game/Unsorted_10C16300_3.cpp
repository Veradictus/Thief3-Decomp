// Game/Unsorted_10C16300_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    void FUN_10bfbd70(int Count);

    ~Class_10BFBD70()
    {
        FUN_10bfbd70(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E98C88;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E98C88* Obj, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E98C88
{
public:
    Class_10E98C88();

    virtual ~Class_10E98C88();

    Class_10BFBD70 Unknown04;
};

// FUNCTION: 0x10C16390 ??0Class_10E98C88@@QAE@XZ
Class_10E98C88::Class_10E98C88()
{
    DAT_10f46da0->Virtual1(this, 0x26, -1, -1);
}
