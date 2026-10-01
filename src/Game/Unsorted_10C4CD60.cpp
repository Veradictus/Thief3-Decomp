// Game/Unsorted_10C4CD60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C4D230
{
    char Unknown00[8];
    int Unknown08;
};

class Class_10c4d140
{
public:
    void FUN_10c4d140(int p1);
};

class Class_10E9BBC0
{
public:
    virtual void Virtual0();
    virtual void FUN_10c4d230(Struct_10C4D230* p1);

    char Unknown04[0x3c];
    Class_10c4d140 Unknown40;
};

class Class_10EC0560
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
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void FUN_10c4d3a0(int p1);
    virtual void FUN_10c4d3b0(int p1);

    char Unknown04[0x1C];
    int Unknown20;
    int Unknown24;
};

struct Elem_10C4DE40
{
    int Unknown00;
    int Unknown04;
    char Unknown08[8];
};

class Class_10c4de40
{
public:
    char Unknown00[0x10];
    Elem_10C4DE40* Unknown10;

    int FUN_10c4de40(int Index);
};

struct Struct_10C4ED70
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C4ED70
{
public:
    void* FUN_10c5cc60(int A, int B);
    void FUN_10c4ed70(int A, int B, int* C);
};

// FUNCTION: 0x10C4D230 ?FUN_10c4d230@Class_10E9BBC0@@UAEXPAUStruct_10C4D230@@@Z
void Class_10E9BBC0::FUN_10c4d230(Struct_10C4D230* p1)
{
    Unknown40.FUN_10c4d140(p1->Unknown08);
}

// FUNCTION: 0x10C4D3A0 ?FUN_10c4d3a0@Class_10EC0560@@UAEXH@Z
void Class_10EC0560::FUN_10c4d3a0(int p1)
{
    Unknown20 = p1;
}

// FUNCTION: 0x10C4D3B0 ?FUN_10c4d3b0@Class_10EC0560@@UAEXH@Z
void Class_10EC0560::FUN_10c4d3b0(int p1)
{
    Unknown24 = p1;
}

// FUNCTION: 0x10C4DE40 ?FUN_10c4de40@Class_10c4de40@@QAEHH@Z
int Class_10c4de40::FUN_10c4de40(int Index)
{
    return Unknown10[Index].Unknown04;
}

// FUNCTION: 0x10C4ED70 ?FUN_10c4ed70@Class_10C4ED70@@QAEXHHPAH@Z
void Class_10C4ED70::FUN_10c4ed70(int A, int B, int* C)
{
    Struct_10C4ED70* Node = (Struct_10C4ED70*)FUN_10c5cc60(1, 0);
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = *C;
    }
}
