// Game/Unsorted_10A928D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

// FUN_10a92670 is the constructor: it stores the vtable and returns this.
class Class_10A92670
{
public:
    Class_10A92670* FUN_10a92670();

    void* Unknown00;
};

class Class_10E5D944
{
public:
    virtual Class_10A92670* FUN_10a928d0();
};

// FUN_10a928c0 is the constructor: it stores the vtable and returns this.
class Class_10A928C0
{
public:
    Class_10A928C0* FUN_10a928c0();

    void* Unknown00;
};

class Class_10E5D940
{
public:
    virtual Class_10A928C0* FUN_10a92920();
};

// FUNCTION: 0x10A928D0 ?FUN_10a928d0@Class_10E5D944@@UAEPAVClass_10A92670@@XZ
Class_10A92670* Class_10E5D944::FUN_10a928d0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A92670* Result = 0;
    void* Memory = operator new(sizeof(Class_10A92670), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A92670*>(Memory)->FUN_10a92670();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A92920 ?FUN_10a92920@Class_10E5D940@@UAEPAVClass_10A928C0@@XZ
Class_10A928C0* Class_10E5D940::FUN_10a92920()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A928C0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A928C0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A928C0*>(Memory)->FUN_10a928c0();
    FUN_10905aa0()->Virtual9();
    return Result;
}
