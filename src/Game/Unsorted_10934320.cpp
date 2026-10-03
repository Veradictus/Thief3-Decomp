// Game/Unsorted_10934320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E49EE0_Member
{
public:
    virtual void __stdcall Virtual0();
    virtual void __stdcall Virtual1();
    virtual void __stdcall Virtual2();
};

class Class_10E49F0C
{
public:
    virtual int FUN_109341e0();
    virtual int FUN_109341f0();
    virtual void Virtual2();
    virtual void Virtual3() = 0;
    virtual unsigned int FUN_10934260() = 0;
    virtual void Virtual5();
    virtual void Virtual6() = 0;
    virtual int FUN_10934a20() = 0;
    virtual int FUN_109342f0(int A) = 0;
    virtual void Virtual9() = 0;
    virtual ~Class_10E49F0C()
    {
        Unknown04 = 0;
        Unknown0C = -1;
        Unknown08 = 0;
        Unknown10 = 0;
    }

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

class Class_10E49EE0 : public Class_10E49F0C
{
public:
    virtual int FUN_109341e0();
    virtual int FUN_109341f0();
    virtual void Virtual3();
    virtual unsigned int FUN_10934260();
    virtual void Virtual6();
    virtual int FUN_10934a20();
    virtual int FUN_109342f0(int A);
    virtual void Virtual9();
    virtual ~Class_10E49EE0();

    Class_10E49EE0_Member* Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
};

// FUNCTION: 0x10934340 ??1Class_10E49EE0@@UAE@XZ
Class_10E49EE0::~Class_10E49EE0()
{
    if (Unknown14)
    {
        Unknown14->Virtual2();
        Unknown14 = 0;
    }
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
}
