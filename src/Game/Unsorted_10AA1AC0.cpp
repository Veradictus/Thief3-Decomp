// Game/Unsorted_10AA1AC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10978090
{
public:
    int FUN_10978090();
};

class Class_10AA1AC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Class_10978090* Virtual4(int A);
};

void FUN_10a36cf0();

void FUN_10a36cd0();

class Class_10E6D3A8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10aa1ac0(int A, int B, Class_10AA1AC0* C);
};

// FUNCTION: 0x10AA1AC0 ?FUN_10aa1ac0@Class_10E6D3A8@@UAEHHHPAVClass_10AA1AC0@@@Z
int Class_10E6D3A8::FUN_10aa1ac0(int A, int B, Class_10AA1AC0* C)
{
    if (C->Virtual4(0)->FUN_10978090() == 1)
    {
        FUN_10a36cf0();
        return 1;
    }
    FUN_10a36cd0();
    return 1;
}
