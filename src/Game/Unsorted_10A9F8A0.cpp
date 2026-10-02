// Game/Unsorted_10A9F8A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a9f870 is the constructor: it stores the vtable and returns this.
class Class_10A9F870
{
public:
    Class_10A9F870* FUN_10a9f870();

    void* Unknown00;
};

class Class_10E5D900
{
public:
    virtual Class_10A9F870* FUN_10a9f8a0();
};

// FUN_10a9f890 is the constructor: it stores the vtable and returns this.
class Class_10A9F890
{
public:
    Class_10A9F890* FUN_10a9f890();

    void* Unknown00;
};

class Class_10E5D8FC
{
public:
    virtual Class_10A9F890* FUN_10a9f8f0();
};

// FUNCTION: 0x10A9F8A0 ?FUN_10a9f8a0@Class_10E5D900@@UAEPAVClass_10A9F870@@XZ
Class_10A9F870* Class_10E5D900::FUN_10a9f8a0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9F870* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9F870), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9F870*>(Memory)->FUN_10a9f870();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9F8F0 ?FUN_10a9f8f0@Class_10E5D8FC@@UAEPAVClass_10A9F890@@XZ
Class_10A9F890* Class_10E5D8FC::FUN_10a9f8f0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9F890* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9F890), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9F890*>(Memory)->FUN_10a9f890();
    FUN_10905aa0()->Virtual9();
    return Result;
}
