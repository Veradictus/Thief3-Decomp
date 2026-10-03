// Game/Unsorted_10A48160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E678F0;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E678F0* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E678F0
{
public:
    virtual ~Class_10E678F0();

    Class_10BFBD70 Unknown04;
    Class_10BFBD70 Unknown10;
};

class Class_10A1FB50
{
public:
    int FUN_10a1fad0(int A);
};

class Class_10A1F9D0
{
public:
    int FUN_10a1f8a0(int A);
};

class Class_10A1F880
{
public:
    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

Class_10A1F880* FUN_10a1fcf0();

class Class_10B59F70
{
public:
    int FUN_10b59f70();
};

// FUNCTION: 0x10A481F0 ?FUN_10a481f0@@YAHHH@Z
int FUN_10a481f0(int A, int B)
{
    if (B >= 0)
        return ((Class_10A1FB50*)FUN_10a1fcf0())->FUN_10a1fad0(B);
    if (A)
        return ((Class_10A1F9D0*)FUN_10a1fcf0())->FUN_10a1f8a0(A);
    return ((Class_10B59F70*)FUN_10a1fcf0())->FUN_10b59f70();
}

// FUNCTION: 0x10A484D0 ??1Class_10E678F0@@UAE@XZ
Class_10E678F0::~Class_10E678F0()
{
    DAT_10f46da0->Virtual2(this);
}
