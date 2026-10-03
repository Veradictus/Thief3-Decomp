// Game/Unsorted_10C2F970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C32C70
{
public:
    void FUN_10c325e0(int A);
    void FUN_10c32c70();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10E9AC80
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual bool FUN_10c32a70(void* A);

    void FUN_10c32970(void* A, int B);
};

class Class_10C30700_Unknown140
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int A, int B);
};

class Class_10C30700
{
public:
    void FUN_10c30700();
    void FUN_10c30750(int A, int B);

    char Unknown00[0x99];
    bool Unknown99;
    char Unknown9A[0x9E];
    int Unknown138;
    char Unknown13C[4];
    Class_10C30700_Unknown140** Unknown140;
};

// FUNCTION: 0x10C30700 ?FUN_10c30700@Class_10C30700@@QAEXXZ
void Class_10C30700::FUN_10c30700()
{
    Unknown99 = true;
    for (int i = 0; i < Unknown138; i++)
        Unknown140[i]->Virtual0();
    Unknown99 = false;
}

// FUNCTION: 0x10C30750 ?FUN_10c30750@Class_10C30700@@QAEXHH@Z
void Class_10C30700::FUN_10c30750(int A, int B)
{
    Unknown99 = true;
    for (int i = 0; i < Unknown138; i++)
        Unknown140[i]->Virtual1(A, B);
    Unknown99 = false;
}

// FUNCTION: 0x10C32A70 ?FUN_10c32a70@Class_10E9AC80@@UAE_NPAX@Z
bool Class_10E9AC80::FUN_10c32a70(void* A)
{
    if (!A)
        return false;
    FUN_10c32970(A, 0);
    return true;
}

// FUNCTION: 0x10C32C70 ?FUN_10c32c70@Class_10C32C70@@QAEXXZ
void Class_10C32C70::FUN_10c32c70()
{
    FUN_10c325e0(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
