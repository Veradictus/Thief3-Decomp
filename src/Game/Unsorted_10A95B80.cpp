// Game/Unsorted_10A95B80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6ce78[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CE78 : public Class_10EB766C
{
public:
    Class_10E6CE78()
    {
        VTable = DAT_10e6ce78;
    }
};

class Class_10E5D824
{
public:
    virtual Class_10E6CE78* FUN_10a95bb0();
};

// FUN_10a95b60 is the constructor: it stores the vtable and returns this.
class Class_10A95B60
{
public:
    Class_10A95B60* FUN_10a95b60();

    void* Unknown00;
};

class Class_10E5D9AC
{
public:
    virtual Class_10A95B60* FUN_10a95c50();
};

// FUNCTION: 0x10A95BB0 ?FUN_10a95bb0@Class_10E5D824@@UAEPAVClass_10E6CE78@@XZ
Class_10E6CE78* Class_10E5D824::FUN_10a95bb0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CE78* Result = new(0, 0, 0, 0, 0) Class_10E6CE78;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95C50 ?FUN_10a95c50@Class_10E5D9AC@@UAEPAVClass_10A95B60@@XZ
Class_10A95B60* Class_10E5D9AC::FUN_10a95c50()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95B60* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95B60), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95B60*>(Memory)->FUN_10a95b60();
    FUN_10905aa0()->Virtual9();
    return Result;
}
