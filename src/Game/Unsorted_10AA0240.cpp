// Game/Unsorted_10AA0240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10aa0210 is the constructor: it stores the vtable and returns this.
class Class_10AA0210
{
public:
    Class_10AA0210* FUN_10aa0210();

    void* Unknown00;
};

class Class_10E5D90C
{
public:
    virtual Class_10AA0210* FUN_10aa0240();
};

// FUN_10aa0230 is the constructor: it stores the vtable and returns this.
class Class_10AA0230
{
public:
    Class_10AA0230* FUN_10aa0230();

    void* Unknown00;
};

class Class_10E5D908
{
public:
    virtual Class_10AA0230* FUN_10aa0290();
};

// FUNCTION: 0x10AA0240 ?FUN_10aa0240@Class_10E5D90C@@UAEPAVClass_10AA0210@@XZ
Class_10AA0210* Class_10E5D90C::FUN_10aa0240()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0210* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0210), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0210*>(Memory)->FUN_10aa0210();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10AA0290 ?FUN_10aa0290@Class_10E5D908@@UAEPAVClass_10AA0230@@XZ
Class_10AA0230* Class_10E5D908::FUN_10aa0290()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0230* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0230), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0230*>(Memory)->FUN_10aa0230();
    FUN_10905aa0()->Virtual9();
    return Result;
}
