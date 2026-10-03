// Game/Unsorted_10A80D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA7530;

class Class_10E6C1F0
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual bool FUN_10a80d90(int A);
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34(int A);
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void FUN_10a80de0(int A, int B);

    int Unknown04;
    char Unknown08[4];
    Class_10AA7530** Unknown0C;
    char Unknown10[4];
    int Unknown14;
    int Unknown18;
    char Unknown1C[4];
    int* Unknown20;
};

class Class_10AA7530
{
public:
    virtual void Virtual0();
    virtual int Virtual1();

    void FUN_10aa7530(int A, int B);
};

// FUNCTION: 0x10A80D90 ?FUN_10a80d90@Class_10E6C1F0@@UAE_NH@Z
bool Class_10E6C1F0::FUN_10a80d90(int A)
{
    if (A != 0 && A == Unknown14)
    {
        while (Unknown18 != 0)
            Virtual34(*Unknown20);
        Unknown14 = 0;
        return true;
    }
    return false;
}

// FUNCTION: 0x10A80DE0 ?FUN_10a80de0@Class_10E6C1F0@@UAEXHH@Z
void Class_10E6C1F0::FUN_10a80de0(int A, int B)
{
    for (int i = 0; i < Unknown04; i++)
    {
        if (!Unknown0C[i]->Virtual1())
            Unknown0C[i]->FUN_10aa7530(A, B);
    }
}
