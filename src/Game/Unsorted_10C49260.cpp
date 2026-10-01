// Game/Unsorted_10C49260.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D3F830
{
public:
    bool FUN_10d3f830(int* p1);
};

struct Struct_10C49860
{
    int Unknown00;
    int Unknown04;
};

class Class_10E9BBC0
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
    virtual void Virtual8();
    virtual void FUN_10c49860(Struct_10C49860* A);

    Class_10D3F830 Unknown04;
};

int FUN_10c48c80(int A);

class Class_10E9BB8C
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void FUN_10c49f50(int A);

    void FUN_10c49340(int A);
};

// FUNCTION: 0x10C49860 ?FUN_10c49860@Class_10E9BBC0@@UAEXPAUStruct_10C49860@@@Z
void Class_10E9BBC0::FUN_10c49860(Struct_10C49860* A)
{
    int Key = A->Unknown04;
    Unknown04.FUN_10d3f830(&Key);
}

// FUNCTION: 0x10C49F50 ?FUN_10c49f50@Class_10E9BB8C@@UAEXH@Z
void Class_10E9BB8C::FUN_10c49f50(int A)
{
    FUN_10c49340(FUN_10c48c80(A));
}
