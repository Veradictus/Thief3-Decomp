// Game/Unsorted_10AB0150.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AB0150_Member
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
};

class Class_10E6DD68
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10ab0150();

    char Unknown04[0x20];
    Class_10AB0150_Member* Unknown24;
};

struct Struct_10AB0330
{
    int Unknown00;
    int Unknown04;
    int Unknown08;

    Struct_10AB0330(int A, int B, const int& C)
    {
        Unknown00 = A;
        Unknown04 = B;
        Unknown08 = C;
    }
};

// FUNCTION: 0x10AB0150 ?FUN_10ab0150@Class_10E6DD68@@UAEXXZ
void Class_10E6DD68::FUN_10ab0150()
{
    Unknown24->Virtual6();
}

// FUNCTION: 0x10AB0330 ?FUN_10ab0330@@YGXHHPAH@Z
void __stdcall FUN_10ab0330(int A, int B, int* C)
{
    new Struct_10AB0330(A, B, *C);
}
