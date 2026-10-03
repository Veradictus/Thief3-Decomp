// Game/Unsorted_10B491C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7E5C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual int FUN_10b49200(int A, int B);
};

struct Struct_10B491C0_Result
{
    char Unknown00[0xC];
    int Unknown0C;
};

class Class_10B491C0_UnknownB0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Struct_10B491C0_Result* Virtual6();
};

struct Struct_10B19300_Param
{
    char Unknown00[0xB0];
    Class_10B491C0_UnknownB0* UnknownB0;
};

class Class_10B19300
{
public:
    void FUN_10b19300(Struct_10B19300_Param* A, float B);
};

Class_10B19300* FUN_10b190e0();

class Class_10E7E580
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10b491c0(Struct_10B19300_Param* A);
};

// FUNCTION: 0x10B491C0 ?FUN_10b491c0@Class_10E7E580@@UAEHPAUStruct_10B19300_Param@@@Z
int Class_10E7E580::FUN_10b491c0(Struct_10B19300_Param* A)
{
    FUN_10b190e0()->FUN_10b19300(A, 1.0f);
    if (A->UnknownB0->Virtual6()->Unknown0C == 1)
        return 0;
    return Virtual4();
}

// FUNCTION: 0x10B49200 ?FUN_10b49200@Class_10E7E5C8@@UAEHHH@Z
int Class_10E7E5C8::FUN_10b49200(int A, int B)
{
    if (B == 0x3c || B == 0x44)
        return 0;
    return Virtual4();
}
