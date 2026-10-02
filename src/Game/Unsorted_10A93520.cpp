// Game/Unsorted_10A93520.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a93350 is the constructor: it stores the vtable and returns this.
class Class_10A93350
{
public:
    Class_10A93350* FUN_10a93350();

    void* Unknown00;
};

class Class_10E5D918
{
public:
    virtual Class_10A93350* FUN_10a93520();
};

// FUN_10a93370 is the constructor: it stores the vtable and returns this.
class Class_10A93370
{
public:
    Class_10A93370* FUN_10a93370();

    void* Unknown00;
};

class Class_10E5D91C
{
public:
    virtual Class_10A93370* FUN_10a93570();
};

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6cc7c[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CC7C : public Class_10EB766C
{
public:
    Class_10E6CC7C()
    {
        VTable = DAT_10e6cc7c;
    }
};

class Class_10E5D7EC
{
public:
    virtual Class_10E6CC7C* FUN_10a935c0();
};

// FUN_10a93500 is the constructor: it stores the vtable and returns this.
class Class_10A93500
{
public:
    Class_10A93500* FUN_10a93500();

    void* Unknown00;
};

class Class_10E5D914
{
public:
    virtual Class_10A93500* FUN_10a93870();
};

// FUNCTION: 0x10A93520 ?FUN_10a93520@Class_10E5D918@@UAEPAVClass_10A93350@@XZ
Class_10A93350* Class_10E5D918::FUN_10a93520()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93350* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93350), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93350*>(Memory)->FUN_10a93350();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93570 ?FUN_10a93570@Class_10E5D91C@@UAEPAVClass_10A93370@@XZ
Class_10A93370* Class_10E5D91C::FUN_10a93570()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93370* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93370), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93370*>(Memory)->FUN_10a93370();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A935C0 ?FUN_10a935c0@Class_10E5D7EC@@UAEPAVClass_10E6CC7C@@XZ
Class_10E6CC7C* Class_10E5D7EC::FUN_10a935c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CC7C* Result = new(0, 0, 0, 0, 0) Class_10E6CC7C;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A93870 ?FUN_10a93870@Class_10E5D914@@UAEPAVClass_10A93500@@XZ
Class_10A93500* Class_10E5D914::FUN_10a93870()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A93500* Result = 0;
    void* Memory = operator new(sizeof(Class_10A93500), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A93500*>(Memory)->FUN_10a93500();
    FUN_10905aa0()->Virtual9();
    return Result;
}
