// Game/Unsorted_10C142C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C14320
{
    char Unknown00[0x78];
    int Unknown78;
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
    virtual Struct_10C14320* Virtual8();
};

class Class_10978090
{
public:
    virtual void Virtual0();

    Class_10C08940* FUN_10978090();

    int Unknown04;
    int Unknown08;
};

class Class_10E8C35C_Secondary
{
public:
    virtual void Virtual0();
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E8C35C_Secondary* A, int B, Struct_10C14320* C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E8C35C : public Class_10978090, public Class_10E8C35C_Secondary
{
public:
    virtual void Virtual1();
    virtual void FUN_10c14320();

    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10C14320 ?FUN_10c14320@Class_10E8C35C@@UAEXXZ
void Class_10E8C35C::FUN_10c14320()
{
    Struct_10C14320* Obj = FUN_10978090()->Virtual8();
    if (Obj->Unknown78 & 4)
    {
        DAT_10f46da0->Virtual1(this, 0x57, Obj, -1);
        Unknown14 = 4;
    }
}
