// Game/Unsorted_10BF6BE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E979DC_Primary
{
public:
    virtual void Virtual0(int Value);
    virtual void Virtual1(int Value);
};

class Class_10E9799C
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
};

class Class_10E5B578
{
public:
    virtual void FUN_10bf8c90(int Code, int A, int B, int C) = 0;
};

class Class_10E979DC : public Class_10E979DC_Primary, public Class_10E9799C, public Class_10E5B578
{
public:
    void FUN_10bf8b40(int A, int B, int C);
    virtual void FUN_10bf8c90(int Code, int A, int B, int C);
};

class Class_10BFB8C0
{
public:
    float FUN_10bfb8c0(int Index);

    float Unknown00[1];
};

class Class_10BFB910
{
public:
    void FUN_10bfb910(int Index);

    int Unknown00[64];
};

class Class_10E6D8F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10bfbb50(int param);
    char Unknown04[0x14];
    int Unknown18;
};

class Class_10E9CD90
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
    virtual void FUN_10bfbb80(int param);
    char Unknown04[0x38];
    int Unknown3C;
};

// FUNCTION: 0x10BF8C90 ?FUN_10bf8c90@Class_10E979DC@@UAEXHHHH@Z
void Class_10E979DC::FUN_10bf8c90(int Code, int A, int B, int C)
{
    if (Code == 4)
        FUN_10bf8b40(A, B, C);
}

// FUNCTION: 0x10BFB8C0 ?FUN_10bfb8c0@Class_10BFB8C0@@QAEMH@Z
float Class_10BFB8C0::FUN_10bfb8c0(int Index)
{
    return Unknown00[Index * 3 + 3];
}

// FUNCTION: 0x10BFB910 ?FUN_10bfb910@Class_10BFB910@@QAEXH@Z
void Class_10BFB910::FUN_10bfb910(int Index)
{
    Unknown00[(Index + 1) * 3] = 0;
}

// FUNCTION: 0x10BFBB50 ?FUN_10bfbb50@Class_10E6D8F0@@UAEXH@Z
void Class_10E6D8F0::FUN_10bfbb50(int param)
{
    Unknown18 = param;
}

// FUNCTION: 0x10BFBB80 ?FUN_10bfbb80@Class_10E9CD90@@UAEXH@Z
void Class_10E9CD90::FUN_10bfbb80(int param)
{
    Unknown3C = param;
}
