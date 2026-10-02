// Game/Unsorted_10A95050.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAB5C0_Result
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int Virtual7(int p1);
};

class Class_10AAB5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    int FUN_10aab5c0();
};

class Class_10E6CE50 : public Class_10AAB5C0
{
public:
    virtual void FUN_10a958f0();

    char Unknown04[8];
    int Unknown0C;
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

// FUN_10a94b00 is the constructor: it stores the vtable and returns this.
class Class_10A94B00
{
public:
    Class_10A94B00* FUN_10a94b00();

    void* Unknown00;
};

class Class_10E5D96C
{
public:
    virtual Class_10A94B00* FUN_10a95050();
};

// FUN_10a94b70 is the constructor: it stores the vtable and returns this.
class Class_10A94B70
{
public:
    Class_10A94B70* FUN_10a94b70();

    void* Unknown00;
};

class Class_10E5D970
{
public:
    virtual Class_10A94B70* FUN_10a950a0();
};

// FUN_10a94c00 is the constructor: it stores the vtable and returns this.
class Class_10A94C00
{
public:
    Class_10A94C00* FUN_10a94c00();

    void* Unknown00;
};

class Class_10E5D974
{
public:
    virtual Class_10A94C00* FUN_10a950f0();
};

// FUN_10a94c80 is the constructor: it stores the vtable and returns this.
class Class_10A94C80
{
public:
    Class_10A94C80* FUN_10a94c80();

    void* Unknown00;
};

class Class_10E5D978
{
public:
    virtual Class_10A94C80* FUN_10a95140();
};

// FUN_10a94c90 is the constructor: it stores the vtable and returns this.
class Class_10A94C90
{
public:
    Class_10A94C90* FUN_10a94c90();

    void* Unknown00;
};

class Class_10E5D97C
{
public:
    virtual Class_10A94C90* FUN_10a95190();
};

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e6ce00[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E6CE00 : public Class_10EB766C
{
public:
    Class_10E6CE00()
    {
        VTable = DAT_10e6ce00;
    }
};

class Class_10E5D808
{
public:
    virtual Class_10E6CE00* FUN_10a951e0();
};

// FUN_10a95040 is the constructor: it stores the vtable and returns this.
class Class_10A95040
{
public:
    Class_10A95040* FUN_10a95040();

    void* Unknown00;
};

class Class_10E5D968
{
public:
    virtual Class_10A95040* FUN_10a95590();
};

// FUNCTION: 0x10A95050 ?FUN_10a95050@Class_10E5D96C@@UAEPAVClass_10A94B00@@XZ
Class_10A94B00* Class_10E5D96C::FUN_10a95050()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A94B00* Result = 0;
    void* Memory = operator new(sizeof(Class_10A94B00), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A94B00*>(Memory)->FUN_10a94b00();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A950A0 ?FUN_10a950a0@Class_10E5D970@@UAEPAVClass_10A94B70@@XZ
Class_10A94B70* Class_10E5D970::FUN_10a950a0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A94B70* Result = 0;
    void* Memory = operator new(sizeof(Class_10A94B70), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A94B70*>(Memory)->FUN_10a94b70();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A950F0 ?FUN_10a950f0@Class_10E5D974@@UAEPAVClass_10A94C00@@XZ
Class_10A94C00* Class_10E5D974::FUN_10a950f0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A94C00* Result = 0;
    void* Memory = operator new(sizeof(Class_10A94C00), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A94C00*>(Memory)->FUN_10a94c00();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95140 ?FUN_10a95140@Class_10E5D978@@UAEPAVClass_10A94C80@@XZ
Class_10A94C80* Class_10E5D978::FUN_10a95140()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A94C80* Result = 0;
    void* Memory = operator new(sizeof(Class_10A94C80), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A94C80*>(Memory)->FUN_10a94c80();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95190 ?FUN_10a95190@Class_10E5D97C@@UAEPAVClass_10A94C90@@XZ
Class_10A94C90* Class_10E5D97C::FUN_10a95190()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A94C90* Result = 0;
    void* Memory = operator new(sizeof(Class_10A94C90), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A94C90*>(Memory)->FUN_10a94c90();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A951E0 ?FUN_10a951e0@Class_10E5D808@@UAEPAVClass_10E6CE00@@XZ
Class_10E6CE00* Class_10E5D808::FUN_10a951e0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E6CE00* Result = new(0, 0, 0, 0, 0) Class_10E6CE00;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A95590 ?FUN_10a95590@Class_10E5D968@@UAEPAVClass_10A95040@@XZ
Class_10A95040* Class_10E5D968::FUN_10a95590()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A95040* Result = 0;
    void* Memory = operator new(sizeof(Class_10A95040), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A95040*>(Memory)->FUN_10a95040();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10A958F0 ?FUN_10a958f0@Class_10E6CE50@@UAEXXZ
void Class_10E6CE50::FUN_10a958f0()
{
    Unknown0C = ((Class_10AAB5C0_Result*)FUN_10aab5c0())->Virtual7(0);
}
