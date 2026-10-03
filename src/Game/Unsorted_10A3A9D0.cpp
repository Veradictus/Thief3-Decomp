// Game/Unsorted_10A3A9D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10A3ACD0
{
public:
    void FUN_1091a960(int Count);
    void FUN_10a3acd0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10A3AC50_Item
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool Virtual3();
    virtual void Virtual4(int A);
};

class Class_10A3AC50_Primary
{
public:
    virtual void Virtual0();
};

class Class_10E667AC
{
public:
    virtual void Virtual0();
    virtual void FUN_10a3ac50(int A);
    virtual void FUN_10a3a330();
    virtual void FUN_10a3a380();

    char Unknown04[0x40];
    int Unknown44;
    char Unknown48[4];
    Class_10A3AC50_Item** Unknown4C;
};

class Class_10A3AC50 : public Class_10A3AC50_Primary, public Class_10E667AC
{
public:
    virtual void FUN_10a3ac50(int A);
    void FUN_10a3abd0(int Index);
};

// FUNCTION: 0x10A3AC50 ?FUN_10a3ac50@Class_10A3AC50@@UAEXH@Z
void Class_10A3AC50::FUN_10a3ac50(int A)
{
    for (int i = 0; i < Unknown44; i++)
    {
        Class_10A3AC50_Item* Item = Unknown4C[i];
        Item->Virtual4(A);
        if (Item->Virtual3())
            FUN_10a3abd0(i);
    }
}

// FUNCTION: 0x10A3ACD0 ?FUN_10a3acd0@Class_10A3ACD0@@QAEXXZ
void Class_10A3ACD0::FUN_10a3acd0()
{
    FUN_1091a960(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
