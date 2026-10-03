// Game/Unsorted_10A93D60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A174E0
{
public:
    virtual int Virtual0(int A);
};

Class_10A174E0* FUN_10a18230();

class Class_10D52BD0
{
public:
    void FUN_10d52bd0();
};

Class_10D52BD0* __stdcall FUN_10d52dd0(int A, int B);

struct Struct_10A93D60
{
    int Unknown00;
    int Unknown04;
};

class Class_10A93D00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Struct_10A93D60* Virtual4(int A);
    virtual int Virtual5(int A);
};

class Class_10E6CCA4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a93d60(int A, int B, Class_10A93D00* C);
};

// FUNCTION: 0x10A93D60 ?FUN_10a93d60@Class_10E6CCA4@@UAEHHHPAVClass_10A93D00@@@Z
int Class_10E6CCA4::FUN_10a93d60(int A, int B, Class_10A93D00* C)
{
    int First = C->Virtual5(0);
    Struct_10A93D60* Second = C->Virtual4(1);
    Class_10A174E0* Manager = FUN_10a18230();
    int Id = Second->Unknown04;
    FUN_10d52dd0(First, Manager->Virtual0(Id))->FUN_10d52bd0();
    return 1;
}
