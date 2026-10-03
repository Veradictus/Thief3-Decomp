// Game/Unsorted_10B26940_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B42340
{
public:
    void FUN_10b42300(int A, int B);
    void FUN_10b425b0(float A);
};

class Class_10E7AAE8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10b26940(float A);
    virtual void Virtual6();
    virtual void FUN_10b26970(int A, int B);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Class_10B42340** Unknown10;
};

// FUNCTION: 0x10B26940 ?FUN_10b26940@Class_10E7AAE8@@UAEXM@Z
void Class_10E7AAE8::FUN_10b26940(float A)
{
    for (int i = 0; i < Unknown08; i++)
        Unknown10[i]->FUN_10b425b0(A);
}
