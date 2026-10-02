// Game/Unsorted_10B8FCB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e8984c[];

class Class_10E8984C
{
public:
    Class_10E8984C();

    void** Unknown00;
    int Unknown04;
};

extern void* DAT_10e89a10[];

class Class_10E89AA0
{
public:
    Class_10E89AA0(int A, int B, int C);

    void** Unknown00;
};

class Class_10E89A10 : public Class_10E89AA0
{
public:
    Class_10E89A10* FUN_10b92660(int A, int B);
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

// FUN_10b8fc80 is the constructor: it stores the vtable and returns this.
class Class_10B8FC80
{
public:
    Class_10B8FC80* FUN_10b8fc80();

    void* Unknown00;
};

class Class_10E88D64
{
public:
    virtual Class_10B8FC80* FUN_10b8fcb0();
};

// FUN_10b8fca0 is the constructor: it stores the vtable and returns this.
class Class_10B8FCA0
{
public:
    Class_10B8FCA0* FUN_10b8fca0();

    void* Unknown00;
};

class Class_10E88D60
{
public:
    virtual Class_10B8FCA0* FUN_10b8fd00();
};

// FUNCTION: 0x10B8FCB0 ?FUN_10b8fcb0@Class_10E88D64@@UAEPAVClass_10B8FC80@@XZ
Class_10B8FC80* Class_10E88D64::FUN_10b8fcb0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B8FC80* Result = 0;
    void* Memory = operator new(sizeof(Class_10B8FC80), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B8FC80*>(Memory)->FUN_10b8fc80();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B8FD00 ?FUN_10b8fd00@Class_10E88D60@@UAEPAVClass_10B8FCA0@@XZ
Class_10B8FCA0* Class_10E88D60::FUN_10b8fd00()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B8FCA0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B8FCA0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B8FCA0*>(Memory)->FUN_10b8fca0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B90320 ??0Class_10E8984C@@QAE@XZ
Class_10E8984C::Class_10E8984C()
{
    Unknown00 = DAT_10e8984c;
    Unknown04 = 0;
}

// FUNCTION: 0x10B92660 ?FUN_10b92660@Class_10E89A10@@QAEPAV1@HH@Z
Class_10E89A10* Class_10E89A10::FUN_10b92660(int A, int B)
{
    this->Class_10E89AA0::Class_10E89AA0(0, A, B);
    Unknown00 = DAT_10e89a10;
    return this;
}
