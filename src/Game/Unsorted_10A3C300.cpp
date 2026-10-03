// Game/Unsorted_10A3C300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10A18FC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(int A, int B);
};

Object_10A18FC0* FUN_10a18fc0();

class Class_10A3C2E0
{
public:
    void FUN_10a3c2e0();
    void FUN_10a3c300(bool A);

    char Unknown00[0x20];
    int Unknown20;
    int Unknown24;
    int Unknown28;
    char Unknown2C[2];
    bool Unknown2E;
    char Unknown2F;
    int Unknown30;
};

// FUNCTION: 0x10A3C300 ?FUN_10a3c300@Class_10A3C2E0@@QAEX_N@Z
void Class_10A3C2E0::FUN_10a3c300(bool A)
{
    if (!A)
    {
        Unknown28 = 0;
        Unknown20 = 0;
        Unknown24 = 0;
        Unknown30 = 0;
        FUN_10a18fc0()->Virtual6(0, 0);
    }
    Unknown2E = A;
}
