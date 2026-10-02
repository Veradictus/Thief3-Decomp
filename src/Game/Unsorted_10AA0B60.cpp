// Game/Unsorted_10AA0B60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10aa0a90 is the constructor: it stores the vtable and returns this.
class Class_10AA0A90
{
public:
    Class_10AA0A90* FUN_10aa0a90();

    void* Unknown00;
};

class Class_10E5D958
{
public:
    virtual Class_10AA0A90* FUN_10aa0b60();
};

// FUN_10aa0ab0 is the constructor: it stores the vtable and returns this.
class Class_10AA0AB0
{
public:
    Class_10AA0AB0* FUN_10aa0ab0();

    void* Unknown00;
};

class Class_10E5D94C
{
public:
    virtual Class_10AA0AB0* FUN_10aa0bb0();
};

// FUN_10aa0b00 is the constructor: it stores the vtable and returns this.
class Class_10AA0B00
{
public:
    Class_10AA0B00* FUN_10aa0b00();

    void* Unknown00;
};

class Class_10E5D950
{
public:
    virtual Class_10AA0B00* FUN_10aa0c00();
};

// FUN_10aa0b50 is the constructor: it stores the vtable and returns this.
class Class_10AA0B50
{
public:
    Class_10AA0B50* FUN_10aa0b50();

    void* Unknown00;
};

class Class_10E5D954
{
public:
    virtual Class_10AA0B50* FUN_10aa0c50();
};

// FUNCTION: 0x10AA0B60 ?FUN_10aa0b60@Class_10E5D958@@UAEPAVClass_10AA0A90@@XZ
Class_10AA0A90* Class_10E5D958::FUN_10aa0b60()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0A90* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0A90), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0A90*>(Memory)->FUN_10aa0a90();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10AA0BB0 ?FUN_10aa0bb0@Class_10E5D94C@@UAEPAVClass_10AA0AB0@@XZ
Class_10AA0AB0* Class_10E5D94C::FUN_10aa0bb0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0AB0* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0AB0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0AB0*>(Memory)->FUN_10aa0ab0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10AA0C00 ?FUN_10aa0c00@Class_10E5D950@@UAEPAVClass_10AA0B00@@XZ
Class_10AA0B00* Class_10E5D950::FUN_10aa0c00()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0B00* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0B00), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0B00*>(Memory)->FUN_10aa0b00();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10AA0C50 ?FUN_10aa0c50@Class_10E5D954@@UAEPAVClass_10AA0B50@@XZ
Class_10AA0B50* Class_10E5D954::FUN_10aa0c50()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10AA0B50* Result = 0;
    void* Memory = operator new(sizeof(Class_10AA0B50), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10AA0B50*>(Memory)->FUN_10aa0b50();
    FUN_10905aa0()->Virtual9();
    return Result;
}
