// Game/Unsorted_10A63230.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A63340
{
public:
    void FUN_10a63340(int Index);
};

class Object_10A63310
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int A);
};

class Class_10E6AC50
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
    virtual void FUN_10a63310(int Index);

    char Unknown04[0x10];
    Class_10A63340 Unknown14;
    char Unknown15[7];
    Object_10A63310** Unknown1C;
};

// FUNCTION: 0x10A63310 ?FUN_10a63310@Class_10E6AC50@@UAEXH@Z
void Class_10E6AC50::FUN_10a63310(int Index)
{
    Unknown1C[Index]->Virtual1(0);
    Unknown14.FUN_10a63340(Index);
}
