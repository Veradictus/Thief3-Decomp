// Game/Unsorted_10941C70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e4a668
{
public:
    virtual void FUN_10942000(int A);
    virtual void FUN_10942030(int p1);
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

    void FUN_10948960(int A);

    char Unknown04[0x58];
    int Unknown5C;
    int Unknown60;
};

class Class_10941E90
{
public:
    void FUN_10941e90();

    void* Unknown00;
};

class Class_10941F40
{
public:
    void FUN_10941f40();

    char Unknown00[4];
    void* Unknown04;
};

class Class_10941C40
{
public:
    void FUN_10941b10(int A);
    void FUN_10941cb0(int A, int B, int C, int D, int E, int F, int G, int H, int I, int J, int K, int L);
    void FUN_10941db0(int A, int B, int C, int D, int E, int F, int G, int H, int I, int J, int K, int L, int M);
};

// FUNCTION: 0x10941DB0 ?FUN_10941db0@Class_10941C40@@QAEXHHHHHHHHHHHHH@Z
void Class_10941C40::FUN_10941db0(int A, int B, int C, int D, int E, int F, int G, int H, int I, int J, int K,
                                  int L, int M)
{
    FUN_10941b10(A);
    FUN_10941cb0(B, C, D, E, F, G, H, I, J, K, H, I);
}

// FUNCTION: 0x10941E90 ?FUN_10941e90@Class_10941E90@@QAEXXZ
void Class_10941E90::FUN_10941e90()
{
    if (Unknown00)
        ::operator delete(Unknown00);
    Unknown00 = 0;
}

// FUNCTION: 0x10941F40 ?FUN_10941f40@Class_10941F40@@QAEXXZ
void Class_10941F40::FUN_10941f40()
{
    if (Unknown04)
        ::operator delete(Unknown04);
    Unknown04 = 0;
}

// FUNCTION: 0x10942000 ?FUN_10942000@Class_10e4a668@@UAEXH@Z
void Class_10e4a668::FUN_10942000(int A)
{
    if (Unknown5C & 1)
    {
        FUN_10948960(0);
        Virtual23();
    }
    Unknown60 &= ~0x800;
    Unknown5C = 0;
}
