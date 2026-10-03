// Game/Unsorted_10AC98E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E6FD0C;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E6FD0C* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6FD0C
{
public:
    virtual ~Class_10E6FD0C();

    Class_10BFBD70 Unknown04;
};

// FUNCTION: 0x10AC9950 ??1Class_10E6FD0C@@UAE@XZ
Class_10E6FD0C::~Class_10E6FD0C()
{
    DAT_10f46da0->Virtual2(this);
}
