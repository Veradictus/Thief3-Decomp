// Game/Unsorted_10C4EDA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10C4EDA0
{
public:
    void FUN_10a550b0(int Count);
    void FUN_10c4eda0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C4E970
{
public:
    void FUN_10c4d3c0(int Count);

    void Empty()
    {
        FUN_10c4d3c0(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C4EE60
{
public:
    void FUN_10c4ee60();

    int Unknown00;
    int Unknown04;
    Class_10C4E970 Unknown08;
};

class Class_10C4F450
{
public:
    void FUN_10c4eea0(int Count);
    void FUN_10c4f450();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10C4F970
{
public:
    void FUN_10c4f490(int Count);
    void FUN_10c4f970();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// FUNCTION: 0x10C4EDA0 ?FUN_10c4eda0@Class_10C4EDA0@@QAEXXZ
void Class_10C4EDA0::FUN_10c4eda0()
{
    FUN_10a550b0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C4EE60 ?FUN_10c4ee60@Class_10C4EE60@@QAEXXZ
void Class_10C4EE60::FUN_10c4ee60()
{
    Unknown08.Empty();
}

// FUNCTION: 0x10C4F450 ?FUN_10c4f450@Class_10C4F450@@QAEXXZ
void Class_10C4F450::FUN_10c4f450()
{
    FUN_10c4eea0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10C4F970 ?FUN_10c4f970@Class_10C4F970@@QAEXXZ
void Class_10C4F970::FUN_10c4f970()
{
    FUN_10c4f490(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
