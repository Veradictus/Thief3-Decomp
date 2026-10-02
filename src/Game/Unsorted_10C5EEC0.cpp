// Game/Unsorted_10C5EEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9C990
{
public:
    virtual void FUN_10c5f030(int Code, int A, int B, int C);
    void FUN_10c5e270(int A, int B, int C, int D);
    void FUN_10c5e750();
};

class Class_10E9C9A8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
    virtual bool FUN_10c5f320(Class_10E9C9A8* Other);

    int Unknown04;
};

// FUNCTION: 0x10C5F030 ?FUN_10c5f030@Class_10E9C990@@UAEXHHHH@Z
void Class_10E9C990::FUN_10c5f030(int Code, int A, int B, int C)
{
    switch (Code)
    {
    case 0x5a:
        FUN_10c5e750();
        break;
    case 0x70:
        FUN_10c5e270(A, B, C, 0);
        break;
    }
}

// FUNCTION: 0x10C5F320 ?FUN_10c5f320@Class_10E9C9A8@@UAE_NPAV1@@Z
bool Class_10E9C9A8::FUN_10c5f320(Class_10E9C9A8* Other)
{
    if (Other->Virtual3() == 1)
        return Other->Unknown04 == Unknown04;
    return false;
}
