// Game/Unsorted_10C12AA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8C378
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual int FUN_10c12b10();

    int* Unknown04;
};

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

class Class_10E6BF84
{
public:
    virtual ~Class_10E6BF84() {}
};

class Class_10E984F4 : public Class_10E6BF84
{
public:
    virtual ~Class_10E984F4();

    int* Unknown04;
};

// FUNCTION: 0x10C12AA0 ??1Class_10E984F4@@UAE@XZ
Class_10E984F4::~Class_10E984F4()
{
    if (Unknown04)
    {
        int* Obj = Unknown04 - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C12B10 ?FUN_10c12b10@Class_10E8C378@@UAEHXZ
int Class_10E8C378::FUN_10c12b10()
{
    int Count = Unknown04 == 0 ? 0 : Unknown04[-1];
    return Count > 0;
}
