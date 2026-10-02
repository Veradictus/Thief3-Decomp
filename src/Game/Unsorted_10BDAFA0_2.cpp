// Game/Unsorted_10BDAFA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB8300
{
public:
    void FUN_10bb8300();
};

class Class_10BB8360 : public Class_10BB8300
{
public:
    void FUN_10bb8360(int A, float B, int C);
};

class Class_10BFF280
{
public:
    int FUN_10bff280();
};

class Class_10BFF460 : public Class_10BFF280
{
};

class Class_10BBB410 : public Class_10BB8360
{
public:
    Class_10BFF460* FUN_10bbb410();
};

class Class_10E947B8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10bdafa0();

    Class_10BBB410* Unknown04;
};

// FUNCTION: 0x10BDAFA0 ?FUN_10bdafa0@Class_10E947B8@@UAEXXZ
void Class_10E947B8::FUN_10bdafa0()
{
    Class_10BFF460* Obj = Unknown04->FUN_10bbb410();
    if (Obj)
    {
        Class_10BBB410* Ctrl = Unknown04;
        Ctrl->FUN_10bb8360(Obj->FUN_10bff280(), 1.0f, 0);
    }
    Unknown04->FUN_10bb8300();
}
