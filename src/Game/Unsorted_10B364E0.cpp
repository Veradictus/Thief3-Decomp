// Game/Unsorted_10B364E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AA3520_Member;

class Class_10B1D660
{
public:
    void FUN_10b1d660();
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
    Class_10B1D660* Unknown0C;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E7C3A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10b36620(int p1, int p2, int p3);
};

class Class_10B1B8A0
{
public:
    void FUN_10b1b8a0(int A);
};

Class_10B1B8A0* FUN_10b1b600();

class Class_10B374E0
{
public:
    void FUN_10b374e0(int A, Class_10B374E0* B, int C);

    char Unknown00[0x4];
    int Unknown04;
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

// FUN_10b36240 is the constructor: it stores the vtable and returns this.
class Class_10B36240
{
public:
    Class_10B36240* FUN_10b36240();

    void* Unknown00;
};

class Class_10E79580
{
public:
    virtual Class_10B36240* FUN_10b364e0();
};

// FUN_10b36260 is the constructor: it stores the vtable and returns this.
class Class_10B36260
{
public:
    Class_10B36260* FUN_10b36260();

    void* Unknown00;
};

class Class_10E79578
{
public:
    virtual Class_10B36260* FUN_10b36530();
};

// FUN_10b36280 is the constructor: it stores the vtable and returns this.
class Class_10B36280
{
public:
    Class_10B36280* FUN_10b36280();

    void* Unknown00;
};

class Class_10E7957C
{
public:
    virtual Class_10B36280* FUN_10b36580();
};

// FUN_10b362d0 is the constructor: it stores the vtable and returns this.
class Class_10B362D0
{
public:
    Class_10B362D0* FUN_10b362d0();

    void* Unknown00;
};

class Class_10E79584
{
public:
    virtual Class_10B362D0* FUN_10b365d0();
};

// FUNCTION: 0x10B364E0 ?FUN_10b364e0@Class_10E79580@@UAEPAVClass_10B36240@@XZ
Class_10B36240* Class_10E79580::FUN_10b364e0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36240* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36240), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36240*>(Memory)->FUN_10b36240();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36530 ?FUN_10b36530@Class_10E79578@@UAEPAVClass_10B36260@@XZ
Class_10B36260* Class_10E79578::FUN_10b36530()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36260* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36260), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36260*>(Memory)->FUN_10b36260();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36580 ?FUN_10b36580@Class_10E7957C@@UAEPAVClass_10B36280@@XZ
Class_10B36280* Class_10E7957C::FUN_10b36580()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B36280* Result = 0;
    void* Memory = operator new(sizeof(Class_10B36280), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B36280*>(Memory)->FUN_10b36280();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B365D0 ?FUN_10b365d0@Class_10E79584@@UAEPAVClass_10B362D0@@XZ
Class_10B362D0* Class_10E79584::FUN_10b365d0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10B362D0* Result = 0;
    void* Memory = operator new(sizeof(Class_10B362D0), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10B362D0*>(Memory)->FUN_10b362d0();
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B36620 ?FUN_10b36620@Class_10E7C3A4@@UAEHHHH@Z
int Class_10E7C3A4::FUN_10b36620(int p1, int p2, int p3)
{
    DAT_10f35dec->Unknown0C->FUN_10b1d660();
    return 1;
}

// FUNCTION: 0x10B374E0 ?FUN_10b374e0@Class_10B374E0@@QAEXHPAV1@H@Z
void Class_10B374E0::FUN_10b374e0(int A, Class_10B374E0* B, int C)
{
    if (B->Unknown04 == Unknown04)
        FUN_10b1b600()->FUN_10b1b8a0(A);
}
