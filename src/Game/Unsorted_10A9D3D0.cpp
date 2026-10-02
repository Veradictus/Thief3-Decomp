// Game/Unsorted_10A9D3D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a9d320 is the constructor: it stores the vtable and returns this.
class Class_10A9D320
{
public:
    Class_10A9D320* FUN_10a9d320();

    void* Unknown00;
};

class Class_10E5D8D0
{
public:
    virtual Class_10A9D320* FUN_10a9d3d0();
};

// FUN_10a9d340 is the constructor: it stores the vtable and returns this.
class Class_10A9D340
{
public:
    Class_10A9D340* FUN_10a9d340();

    void* Unknown00;
};

class Class_10E5D8D4
{
public:
    virtual Class_10A9D340* FUN_10a9d420();
};

// FUN_10a9d360 is the constructor: it stores the vtable and returns this.
class Class_10A9D360
{
public:
    Class_10A9D360* FUN_10a9d360();

    void* Unknown00;
};

class Class_10E5D8D8
{
public:
    virtual Class_10A9D360* FUN_10a9d470();
};

// FUN_10a9d380 is the constructor: it stores the vtable and returns this.
class Class_10A9D380
{
public:
    Class_10A9D380* FUN_10a9d380();

    void* Unknown00;
};

class Class_10E5D8DC
{
public:
    virtual Class_10A9D380* FUN_10a9d4c0();
};

// FUN_10a9d3a0 is the constructor: it stores the vtable and returns this.
class Class_10A9D3A0
{
public:
    Class_10A9D3A0* FUN_10a9d3a0();

    void* Unknown00;
};

class Class_10E5D8E0
{
public:
    virtual Class_10A9D3A0* FUN_10a9d510();
};

// FUN_10a9d3c0 is the constructor: it stores the vtable and returns this.
class Class_10A9D3C0
{
public:
    Class_10A9D3C0* FUN_10a9d3c0();

    void* Unknown00;
};

class Class_10E5D8CC
{
public:
    virtual Class_10A9D3C0* FUN_10a9d560();
};

// FUNCTION: 0x10A9D3D0 ?FUN_10a9d3d0@Class_10E5D8D0@@UAEPAVClass_10A9D320@@XZ
Class_10A9D320* Class_10E5D8D0::FUN_10a9d3d0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D320* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D320), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D320*>(Memory)->FUN_10a9d320();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9D420 ?FUN_10a9d420@Class_10E5D8D4@@UAEPAVClass_10A9D340@@XZ
Class_10A9D340* Class_10E5D8D4::FUN_10a9d420()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D340* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D340), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D340*>(Memory)->FUN_10a9d340();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9D470 ?FUN_10a9d470@Class_10E5D8D8@@UAEPAVClass_10A9D360@@XZ
Class_10A9D360* Class_10E5D8D8::FUN_10a9d470()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D360* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D360), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D360*>(Memory)->FUN_10a9d360();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9D4C0 ?FUN_10a9d4c0@Class_10E5D8DC@@UAEPAVClass_10A9D380@@XZ
Class_10A9D380* Class_10E5D8DC::FUN_10a9d4c0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D380* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D380), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D380*>(Memory)->FUN_10a9d380();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9D510 ?FUN_10a9d510@Class_10E5D8E0@@UAEPAVClass_10A9D3A0@@XZ
Class_10A9D3A0* Class_10E5D8E0::FUN_10a9d510()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D3A0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D3A0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D3A0*>(Memory)->FUN_10a9d3a0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A9D560 ?FUN_10a9d560@Class_10E5D8CC@@UAEPAVClass_10A9D3C0@@XZ
Class_10A9D3C0* Class_10E5D8CC::FUN_10a9d560()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D3C0* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D3C0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D3C0*>(Memory)->FUN_10a9d3c0();
    FUN_10905aa0()->Virtual9();
    return Result;
}
