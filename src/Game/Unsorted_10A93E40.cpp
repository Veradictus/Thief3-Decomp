// Game/Unsorted_10A93E40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C890
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual int FUN_10a93fd0(int A);
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

// FUN_10a93d40 is the constructor: it stores the vtable and returns this.
class Class_10A93D40
{
public:
    Class_10A93D40* FUN_10a93d40();

    void* Unknown00;
};

class Class_10E5D960
{
public:
    virtual Class_10A93D40* FUN_10a93e40();
};

// FUN_10a93db0 is the constructor: it stores the vtable and returns this.
class Class_10A93DB0
{
public:
    Class_10A93DB0* FUN_10a93db0();

    void* Unknown00;
};

class Class_10E5D964
{
public:
    virtual Class_10A93DB0* FUN_10a93e90();
};

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6ccbc[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CCBC : public Class_10EB766C
{
public:
    Class_10E6CCBC()
    {
        VTable = DAT_10e6ccbc;
    }
};

class Class_10E5D7F4
{
public:
    virtual Class_10E6CCBC* FUN_10a93ee0();
};

// FUN_10a93e30 is the constructor: it stores the vtable and returns this.
class Class_10A93E30
{
public:
    Class_10A93E30* FUN_10a93e30();

    void* Unknown00;
};

class Class_10E5D95C
{
public:
    virtual Class_10A93E30* FUN_10a93f80();
};

// FUNCTION: 0x10A93E40 ?FUN_10a93e40@Class_10E5D960@@UAEPAVClass_10A93D40@@XZ
Class_10A93D40* Class_10E5D960::FUN_10a93e40()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93D40* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93D40), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93D40*>(Memory)->FUN_10a93d40();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93E90 ?FUN_10a93e90@Class_10E5D964@@UAEPAVClass_10A93DB0@@XZ
Class_10A93DB0* Class_10E5D964::FUN_10a93e90()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93DB0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93DB0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93DB0*>(Memory)->FUN_10a93db0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93EE0 ?FUN_10a93ee0@Class_10E5D7F4@@UAEPAVClass_10E6CCBC@@XZ
Class_10E6CCBC* Class_10E5D7F4::FUN_10a93ee0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CCBC* Result = new(0, 0, 0, 0, 0) Class_10E6CCBC;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93F80 ?FUN_10a93f80@Class_10E5D95C@@UAEPAVClass_10A93E30@@XZ
Class_10A93E30* Class_10E5D95C::FUN_10a93f80()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93E30* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93E30), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93E30*>(Memory)->FUN_10a93e30();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93FD0 ?FUN_10a93fd0@Class_10E6C890@@UAEHH@Z
int Class_10E6C890::FUN_10a93fd0(int A)
{
    return A == Virtual4();
}
