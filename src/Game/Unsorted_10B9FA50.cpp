// Game/Unsorted_10B9FA50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10B9FBE0
{
public:
    void FUN_10b9f620(int Count);
    void FUN_10b9fbe0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10B9FC20
{
public:
    void FUN_10b9f6d0(int Count);
    void FUN_10b9fc20();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E8C008
{
public:
    ~Class_10E8C008();

    virtual void Virtual0();
};

struct Struct_10BA0080
{
    int Count;
    int Unknown04;
    Class_10E8C008** Items;
};

// FUNCTION: 0x10B9FBE0 ?FUN_10b9fbe0@Class_10B9FBE0@@QAEXXZ
void Class_10B9FBE0::FUN_10b9fbe0()
{
    FUN_10b9f620(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10B9FC20 ?FUN_10b9fc20@Class_10B9FC20@@QAEXXZ
void Class_10B9FC20::FUN_10b9fc20()
{
    FUN_10b9f6d0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10BA0080 ?FUN_10ba0080@@YAXPAUStruct_10BA0080@@@Z
void FUN_10ba0080(Struct_10BA0080* Array)
{
    for (int i = 0; i < Array->Count; i++)
        delete Array->Items[i];
    Array->Count = 0;
}
