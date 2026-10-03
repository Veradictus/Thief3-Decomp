// Game/Unsorted_10B8ACF0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B8ACF0
{
public:
    char Unknown00[8];
    void* Unknown08;
    char Unknown0C[0x1C];
    int Unknown28;
};

class Class_10CAF5E0
{
public:
    void FUN_10caf5e0(Object_10B8ACF0* A, int B);
};

class Class_10D9B090
{
public:
    char Unknown00[4];
    Class_10CAF5E0* Unknown04;
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10E894C8
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
    virtual void FUN_10b8acf0(int A);

    void FUN_10d9fe70(int A);

    char Unknown04[0x4C];
    Object_10B8ACF0* Unknown50;
};

// FUNCTION: 0x10B8ACF0 ?FUN_10b8acf0@Class_10E894C8@@UAEXH@Z
void Class_10E894C8::FUN_10b8acf0(int A)
{
    FUN_10d9fe70(A);
    Unknown50->Unknown28 = A;
    if (Unknown50->Unknown08)
    {
        Class_10D9B090* Manager = FUN_10d9dcb0();
        Manager->Unknown04->FUN_10caf5e0(Unknown50, 1);
    }
}
