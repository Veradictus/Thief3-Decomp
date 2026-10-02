// Game/Unsorted_10A33EE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6649C
{
public:
    virtual void FUN_10a34760(int p1, int* p2, int* p3);
};

class Class_10A34B90
{
public:
    void FUN_10a34b90(int A);
    void FUN_10a35140();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10A34CD0
{
public:
    void FUN_10a34cd0(int A);
    void FUN_10a35170();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Object_10AB5B20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5B20
{
public:
    Class_10AB5B20(const Class_10AB5B20& Other)
    {
        Unknown00 = Other.Unknown00;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10AB5B20();

    Object_10AB5B20* Unknown00;
};

struct Info_10A34730
{
    char Unknown00[0x10];
    Class_10AB5B20 Unknown10;
};

class Class_10A34730
{
public:
    Class_10AB5B20 FUN_10a34730();

    Info_10A34730* Unknown00;
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

struct Entry_10A34D50
{
    char Unknown00[0x6C];
};

class Class_10A34D50
{
public:
    void FUN_10a33fd0(int NewCount);
    void FUN_10a346f0();

    int Unknown00;
    int Unknown04;
    Entry_10A34D50* Unknown08;
};

struct Struct_10A33EE0_Vec
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10A33EE0
{
    char Unknown00[0x2C];
    Struct_10A33EE0_Vec Unknown2C;
};

// FUNCTION: 0x10A33EE0 ?FUN_10a33ee0@@YGXPAUStruct_10A33EE0@@0PBUStruct_10A33EE0_Vec@@1@Z
void __stdcall FUN_10a33ee0(Struct_10A33EE0* A, Struct_10A33EE0* B, const Struct_10A33EE0_Vec* C, const Struct_10A33EE0_Vec* D)
{
    if (A)
        A->Unknown2C = *C;
    if (B)
        B->Unknown2C = *D;
}

// FUNCTION: 0x10A346F0 ?FUN_10a346f0@Class_10A34D50@@QAEXXZ
void Class_10A34D50::FUN_10a346f0()
{
    FUN_10a33fd0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10A34730 ?FUN_10a34730@Class_10A34730@@QAE?AVClass_10AB5B20@@XZ
Class_10AB5B20 Class_10A34730::FUN_10a34730()
{
    return Unknown00->Unknown10;
}

// FUNCTION: 0x10A34760 ?FUN_10a34760@Class_10E6649C@@UAEXHPAH0@Z
void Class_10E6649C::FUN_10a34760(int p1, int* p2, int* p3)
{
    *p2 = p1;
    *p3 = 0x10;
}

// FUNCTION: 0x10A35140 ?FUN_10a35140@Class_10A34B90@@QAEXXZ
void Class_10A34B90::FUN_10a35140()
{
    FUN_10a34b90(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}

// FUNCTION: 0x10A35170 ?FUN_10a35170@Class_10A34CD0@@QAEXXZ
void Class_10A34CD0::FUN_10a35170()
{
    FUN_10a34cd0(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
