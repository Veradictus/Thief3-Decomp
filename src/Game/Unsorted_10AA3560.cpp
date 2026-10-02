// Game/Unsorted_10AA3560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA44B0
{
public:
    void FUN_10aa3830(int A);
    void FUN_10aa44b0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
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
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// FUN_10aa3550 is the constructor: it stores the vtable and returns this.
class Class_10AA3550
{
public:
    Class_10AA3550* FUN_10aa3550();

    void* Unknown00;
};

class Class_10E5D9D8
{
public:
    virtual Class_10AA3550* FUN_10aa3580();
};

// FUNCTION: 0x10AA3580 ?FUN_10aa3580@Class_10E5D9D8@@UAEPAVClass_10AA3550@@XZ
Class_10AA3550* Class_10E5D9D8::FUN_10aa3580()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA3550* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA3550), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA3550*>(Memory)->FUN_10aa3550();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10AA44B0 ?FUN_10aa44b0@Class_10AA44B0@@QAEXXZ
void Class_10AA44B0::FUN_10aa44b0()
{
    FUN_10aa3830(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
