// Game/Unsorted_10953AC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_10953AC0;

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

class Class_10953AC0
{
public:
    void FUN_10953ac0(int A);
    void FUN_10953be0();

    int Unknown00;
    int Unknown04;
    Item_10953AC0* Unknown08;
};

class Class_10953C20
{
public:
    Class_10953C20* FUN_10953c20(int A, bool B);

    float Unknown00[4][4];
    float Unknown40;
    float Unknown44;
    float Unknown48;
    int Unknown4C;
    int Unknown50;
    float Unknown54;
    float Unknown58;
    float Unknown5C;
    bool Unknown60;
    bool Unknown61;
    bool Unknown62;
};

// FUNCTION: 0x10953BE0 ?FUN_10953be0@Class_10953AC0@@QAEXXZ
void Class_10953AC0::FUN_10953be0()
{
    FUN_10953ac0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}

// FUNCTION: 0x10953C20 ?FUN_10953c20@Class_10953C20@@QAEPAV1@H_N@Z
Class_10953C20* Class_10953C20::FUN_10953c20(int A, bool B)
{
    Unknown40 = 0.0f;
    Unknown44 = 0.0f;
    Unknown48 = 0.0f;
    Unknown54 = 0.0f;
    Unknown58 = 0.0f;
    Unknown5C = 0.0f;
    Unknown50 = A;
    Unknown00[0][0] = Unknown00[1][1] = Unknown00[2][2] = Unknown00[3][3] = 1.0f;
    Unknown00[0][3] = Unknown00[1][3] = Unknown00[2][3] = 0.0f;
    Unknown00[0][1] = Unknown00[0][2] = Unknown00[1][0] = 0.0f;
    Unknown00[3][0] = Unknown00[3][1] = Unknown00[3][2] = 0.0f;
    Unknown00[1][2] = Unknown00[2][0] = Unknown00[2][1] = 0.0f;
    Unknown60 = false;
    Unknown61 = true;
    Unknown62 = B;
    return this;
}
