// Game/Unsorted_10C4DE80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10C4E8D0
{
public:
    void FUN_10c4d550(int Count);
    void FUN_10c4e8d0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C4E970
{
public:
    void FUN_10c4d3c0(int Count);
    void FUN_10c4e970();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10C4E8D0 ?FUN_10c4e8d0@Class_10C4E8D0@@QAEXXZ
void Class_10C4E8D0::FUN_10c4e8d0()
{
    FUN_10c4d550(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C4E970 ?FUN_10c4e970@Class_10C4E970@@QAEXXZ
void Class_10C4E970::FUN_10c4e970()
{
    FUN_10c4d3c0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
