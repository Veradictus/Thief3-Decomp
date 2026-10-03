// Game/Unsorted_10A92360.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D9FEE0
{
public:
    void FUN_10d9fee0(int A, int B);
};

class Class_10A370C0
{
public:
    char Unknown00[0xB0];
    Class_10D9FEE0* Unknown0B0;
};

class Class_10C08940
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
    virtual Class_10A370C0* Virtual8();
};

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();

    Class_10C08940* Unknown04;
};

class Class_10AAB5C0 : public Class_10978090
{
public:
    int FUN_10aab5c0();

    int Unknown08;
};

class Class_10E6CB20_Second
{
public:
    virtual void SecondVirtual0();
    virtual void SecondVirtual1();
    virtual void SecondVirtual2();
    virtual void SecondVirtual3();
    virtual void SecondVirtual4();
    virtual void SecondVirtual5(Class_10A370C0* A, int B, int C, int D);
};

class Object_10A92470
{
public:
    virtual void Virtual0();
    virtual int Virtual1(int A);
};

class Class_10E6CB20 : public Class_10AAB5C0, public Class_10E6CB20_Second
{
public:
    virtual void Virtual1();
    virtual void FUN_10a92360();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5(int A);
    virtual int FUN_10a92470(int A, Object_10A92470* B);
};

// FUNCTION: 0x10A92360 ?FUN_10a92360@Class_10E6CB20@@UAEXXZ
void Class_10E6CB20::FUN_10a92360()
{
    SecondVirtual5(FUN_10978090()->Virtual8(), 0, 1, 0);
    Class_10A370C0* Obj = FUN_10978090()->Virtual8();
    if (Obj->Unknown0B0)
        Obj->Unknown0B0->FUN_10d9fee0(1, 1);
}

// FUNCTION: 0x10A92470 ?FUN_10a92470@Class_10E6CB20@@UAEHHPAVObject_10A92470@@@Z
int Class_10E6CB20::FUN_10a92470(int A, Object_10A92470* B)
{
    if (Virtual5(A))
        return B->Virtual1(FUN_10aab5c0());
    return 0;
}
