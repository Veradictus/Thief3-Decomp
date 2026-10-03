// Game/Unsorted_10AB7530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10AB90F0
{
public:
    void FUN_10ab8e90(int Count);
    void FUN_10ab90f0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Struct_10AB86C0
{
    int Unknown00;
    char Unknown04[0x2C];
};

class Class_10AB86C0
{
public:
    int FUN_10ab86c0(int Value);

    int FindIndex(int Value)
    {
        for (int i = 0; i < Unknown04; i++)
        {
            if (Value == Unknown0C[i].Unknown00)
                return i;
        }
        return -1;
    }

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10AB86C0* Unknown0C;
};

// FUNCTION: 0x10AB86C0 ?FUN_10ab86c0@Class_10AB86C0@@QAEHH@Z
int Class_10AB86C0::FUN_10ab86c0(int Value)
{
    return FindIndex(Value) >= 0;
}

// FUNCTION: 0x10AB90F0 ?FUN_10ab90f0@Class_10AB90F0@@QAEXXZ
void Class_10AB90F0::FUN_10ab90f0()
{
    FUN_10ab8e90(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
