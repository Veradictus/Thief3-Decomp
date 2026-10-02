// Game/Unsorted_10BB0C90_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40
{
public:
    void FUN_10bbd550(int A, int B);
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

struct Struct_10BB0B90_Unknown118
{
    char Unknown00[0x10];
    Class_10DBD510* Unknown10;
};

class Struct_10BB0B90
{
public:
    char Unknown00[0x118];
    Struct_10BB0B90_Unknown118* Unknown118;
};

Struct_10BB0B90* FUN_10bb0b90(int A);

struct Struct_10BB13D0_Result
{
    char Unknown00[8];
    int Unknown08;
};

class Class_10BB13D0_B
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
    virtual int Virtual8();
};

class Class_10BB13D0_C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Struct_10BB13D0_Result* Virtual4(int A);
};

class Class_10E8C8C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10bb13d0(int A, Class_10BB13D0_B* B, Class_10BB13D0_C* C);
};

// FUNCTION: 0x10BB13D0 ?FUN_10bb13d0@Class_10E8C8C0@@UAEHHPAVClass_10BB13D0_B@@PAVClass_10BB13D0_C@@@Z
int Class_10E8C8C0::FUN_10bb13d0(int A, Class_10BB13D0_B* B, Class_10BB13D0_C* C)
{
    int First = C->Virtual4(0)->Unknown08;
    int Second = B->Virtual8();
    Struct_10BB0B90* Owner = FUN_10bb0b90((int)B);
    if (Owner && Owner->Unknown118 && Owner->Unknown118->Unknown10)
    {
        Class_10BBDB40* Target = Owner->Unknown118->Unknown10->FUN_10dbd510();
        if (Target)
            Target->FUN_10bbd550(First, Second);
    }
    return 1;
}
