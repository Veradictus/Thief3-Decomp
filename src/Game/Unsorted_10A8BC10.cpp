// Game/Unsorted_10A8BC10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10B0D530
{
public:
    ~Class_10B0D530();
};

class Class_10F3A1EC
{
public:
    int Unknown00[5];
    Class_10B0D530 Unknown14;
};

extern Class_10F3A1EC* DAT_10f3a1ec;

class Class_10E6BF84
{
public:
    virtual ~Class_10E6BF84() {}
};

class Class_10E6C68C : public Class_10E6BF84
{
public:
    virtual ~Class_10E6C68C();

    int Unknown04;
    int Unknown08;
    int* Unknown0C;
};

// FUNCTION: 0x10A8BDC0 ??1Class_10E6C68C@@UAE@XZ
Class_10E6C68C::~Class_10E6C68C()
{
    if (DAT_10f3a1ec)
    {
        delete DAT_10f3a1ec;
        DAT_10f3a1ec = 0;
    }
    if (Unknown0C)
    {
        int* Obj = Unknown0C - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown0C = 0;
    }
}
