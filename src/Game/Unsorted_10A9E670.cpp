// Game/Unsorted_10A9E670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a9e4c0 is the constructor: it stores the vtable and returns this.
class Class_10A9E4C0
{
public:
    Class_10A9E4C0* FUN_10a9e4c0();

    void* Unknown00;
};

class Class_10E5D8E8
{
public:
    virtual Class_10A9E4C0* FUN_10a9e670();
};

// FUN_10a9e5e0 is the constructor: it stores the vtable and returns this.
class Class_10A9E5E0
{
public:
    Class_10A9E5E0* FUN_10a9e5e0();

    void* Unknown00;
};

class Class_10E5D8EC
{
public:
    virtual Class_10A9E5E0* FUN_10a9e6c0();
};

// FUN_10a9e600 is the constructor: it stores the vtable and returns this.
class Class_10A9E600
{
public:
    Class_10A9E600* FUN_10a9e600();

    void* Unknown00;
};

class Class_10E5D8F8
{
public:
    virtual Class_10A9E600* FUN_10a9e710();
};

// FUN_10a9e620 is the constructor: it stores the vtable and returns this.
class Class_10A9E620
{
public:
    Class_10A9E620* FUN_10a9e620();

    void* Unknown00;
};

class Class_10E5D8F0
{
public:
    virtual Class_10A9E620* FUN_10a9e760();
};

// FUN_10a9e640 is the constructor: it stores the vtable and returns this.
class Class_10A9E640
{
public:
    Class_10A9E640* FUN_10a9e640();

    void* Unknown00;
};

class Class_10E5D8F4
{
public:
    virtual Class_10A9E640* FUN_10a9e7b0();
};

// FUN_10a9e660 is the constructor: it stores the vtable and returns this.
class Class_10A9E660
{
public:
    Class_10A9E660* FUN_10a9e660();

    void* Unknown00;
};

class Class_10E5D8E4
{
public:
    virtual Class_10A9E660* FUN_10a9e800();
};

// FUNCTION: 0x10A9E670 ?FUN_10a9e670@Class_10E5D8E8@@UAEPAVClass_10A9E4C0@@XZ
Class_10A9E4C0* Class_10E5D8E8::FUN_10a9e670()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E4C0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E4C0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E4C0*>(Memory)->FUN_10a9e4c0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9E6C0 ?FUN_10a9e6c0@Class_10E5D8EC@@UAEPAVClass_10A9E5E0@@XZ
Class_10A9E5E0* Class_10E5D8EC::FUN_10a9e6c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E5E0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E5E0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E5E0*>(Memory)->FUN_10a9e5e0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9E710 ?FUN_10a9e710@Class_10E5D8F8@@UAEPAVClass_10A9E600@@XZ
Class_10A9E600* Class_10E5D8F8::FUN_10a9e710()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E600* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E600), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E600*>(Memory)->FUN_10a9e600();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9E760 ?FUN_10a9e760@Class_10E5D8F0@@UAEPAVClass_10A9E620@@XZ
Class_10A9E620* Class_10E5D8F0::FUN_10a9e760()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E620* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E620), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E620*>(Memory)->FUN_10a9e620();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9E7B0 ?FUN_10a9e7b0@Class_10E5D8F4@@UAEPAVClass_10A9E640@@XZ
Class_10A9E640* Class_10E5D8F4::FUN_10a9e7b0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E640* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E640), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E640*>(Memory)->FUN_10a9e640();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9E800 ?FUN_10a9e800@Class_10E5D8E4@@UAEPAVClass_10A9E660@@XZ
Class_10A9E660* Class_10E5D8E4::FUN_10a9e800()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9E660* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9E660), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9E660*>(Memory)->FUN_10a9e660();
    FUN_10905aa0()->Virtual9();
    return Result;
}
