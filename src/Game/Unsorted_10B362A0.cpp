// Game/Unsorted_10B362A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAB5C0
{
public:
    int FUN_10aab5c0();
};

class Class_10B362A0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Class_10AAB5C0* Virtual4(int A);
};

class Class_10B1B8A0
{
public:
    void FUN_10b1abd0(int A);
};

Class_10B1B8A0* FUN_10b1b600();

class Class_10E7C398
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10b362a0(int A, int B, Class_10B362A0* C);
};

// FUNCTION: 0x10B362A0 ?FUN_10b362a0@Class_10E7C398@@UAEHHHPAVClass_10B362A0@@@Z
int Class_10E7C398::FUN_10b362a0(int A, int B, Class_10B362A0* C)
{
    FUN_10b1b600()->FUN_10b1abd0(C->Virtual4(0)->FUN_10aab5c0());
    return 1;
}
