// Game/Unsorted_10B26940_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B42340
{
public:
    void FUN_10b42300(int A, int B);
    void FUN_10b425b0(float A);
};

class Class_10B42640
{
public:
    void FUN_10b42640();
    void FUN_10b42650(int A, int B);
};

Class_10B42640* FUN_10b42920();

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

// FUNCTION: 0x10B26970 ?FUN_10b26970@Class_10E7AAE8@@UAEXHH@Z
void Class_10E7AAE8::FUN_10b26970(int A, int B)
{
    for (int i = 0; i < Unknown08; i++)
        Unknown10[i]->FUN_10b42300(A, B);
    FUN_10b42920()->FUN_10b42650(A, B);
    FUN_10b42920()->FUN_10b42640();
}
