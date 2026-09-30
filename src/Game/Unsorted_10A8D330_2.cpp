// Game/Unsorted_10A8D330_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C7B4 {
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual bool FUN_10a8d330();
    char Unknown04[4];
    int Unknown08;
};

struct Class_10E6C4A8_Member
{
    int Unknown00;
};

class Class_10E6C4A8
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual void Virtual10() = 0;
    virtual void Virtual11() = 0;
    virtual void FUN_10a8d340(const Class_10E6C4A8* p1);

    Class_10E6C4A8_Member Unknown04;
};

// FUNCTION: 0x10A8D330 ?FUN_10a8d330@Class_10E6C7B4@@UAE_NXZ
bool Class_10E6C7B4::FUN_10a8d330()
{
    return Unknown08 >= 4;
}

// FUNCTION: 0x10A8D340 ?FUN_10a8d340@Class_10E6C4A8@@UAEXPBV1@@Z
void Class_10E6C4A8::FUN_10a8d340(const Class_10E6C4A8* p1)
{
    Unknown04 = p1->Unknown04;
}
