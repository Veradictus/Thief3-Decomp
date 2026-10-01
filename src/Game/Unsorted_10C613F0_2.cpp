// Game/Unsorted_10C613F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Class_10C613F0_Member
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10C613F0
{
public:
    int FUN_10c613f0();

    char Unknown00[0xC];
    Class_10C613F0_Member* Unknown0C;
};

class Class_10C61C20_Param
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
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18(int p1);
};

class Class_10E9CA9C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10c61c20(Class_10C61C20_Param* p1);
};

class Class_10EC0560
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
    virtual int FUN_10c61cd0();

    char Unknown04[0xC];
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10C613F0 ?FUN_10c613f0@Class_10C613F0@@QAEHXZ
int Class_10C613F0::FUN_10c613f0()
{
    if (!Unknown0C)
        return -1;
    return Unknown0C->Unknown0C;
}

// FUNCTION: 0x10C61C20 ?FUN_10c61c20@Class_10E9CA9C@@UAEXPAVClass_10C61C20_Param@@@Z
void Class_10E9CA9C::FUN_10c61c20(Class_10C61C20_Param* p1)
{
    if (p1)
        p1->Virtual18(1);
}

// FUNCTION: 0x10C61CD0 ?FUN_10c61cd0@Class_10EC0560@@UAEHXZ
int Class_10EC0560::FUN_10c61cd0()
{
    if (Unknown14 != 0 && Unknown10 == Unknown14)
        return 1;
    return 0;
}
