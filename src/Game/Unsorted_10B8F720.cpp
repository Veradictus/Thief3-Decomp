// Game/Unsorted_10B8F720.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10b8f6d0 is the constructor: it stores the vtable and returns this.
class Class_10B8F6D0
{
public:
    Class_10B8F6D0* FUN_10b8f6d0();

    void* Unknown00;
};

class Class_10E88D58
{
public:
    virtual Class_10B8F6D0* FUN_10b8f720();
};

// FUN_10b8f6f0 is the constructor: it stores the vtable and returns this.
class Class_10B8F6F0
{
public:
    Class_10B8F6F0* FUN_10b8f6f0();

    void* Unknown00;
};

class Class_10E88D5C
{
public:
    virtual Class_10B8F6F0* FUN_10b8f770();
};

// FUN_10b8f700 is the constructor: it stores the vtable and returns this.
class Class_10B8F700
{
public:
    Class_10B8F700* FUN_10b8f700();

    void* Unknown00;
};

class Class_10E88D54
{
public:
    virtual Class_10B8F700* FUN_10b8f7c0();
};

// FUNCTION: 0x10B8F720 ?FUN_10b8f720@Class_10E88D58@@UAEPAVClass_10B8F6D0@@XZ
Class_10B8F6D0* Class_10E88D58::FUN_10b8f720()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B8F6D0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B8F6D0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B8F6D0*>(Memory)->FUN_10b8f6d0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B8F770 ?FUN_10b8f770@Class_10E88D5C@@UAEPAVClass_10B8F6F0@@XZ
Class_10B8F6F0* Class_10E88D5C::FUN_10b8f770()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B8F6F0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B8F6F0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B8F6F0*>(Memory)->FUN_10b8f6f0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B8F7C0 ?FUN_10b8f7c0@Class_10E88D54@@UAEPAVClass_10B8F700@@XZ
Class_10B8F700* Class_10E88D54::FUN_10b8f7c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B8F700* Result = 0;
    void* Memory = operator new(sizeof(Class_10B8F700), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B8F700*>(Memory)->FUN_10b8f700();
    FUN_10905aa0()->Virtual9();
    return Result;
}
