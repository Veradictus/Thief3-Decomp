// Game/Unsorted_10BB0CD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_10bb0c60(int A);

class Class_10C3D3B0
{
public:
    virtual float FUN_10c3d3b0();
};

class Class_10E9CD90
{
public:
    virtual void FUN_10bfbb80(float param);
};

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BB1140_Item
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
    virtual int Virtual8();
};

class Class_10BB1140_Source
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
    virtual Class_10C3D3B0* Virtual4(int A);
};

class Class_10E8C86C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10bb1140(int p1, Class_10BB1140_Item* Item, Class_10BB1140_Source* Source);
};

// FUNCTION: 0x10BB1140 ?FUN_10bb1140@Class_10E8C86C@@UAEHHPAVClass_10BB1140_Item@@PAVClass_10BB1140_Source@@@Z
int Class_10E8C86C::FUN_10bb1140(int p1, Class_10BB1140_Item* Item, Class_10BB1140_Source* Source)
{
    if (Item && Item->Virtual8() && Source && Source->Virtual3() >= 1)
    {
        int Obj = FUN_10bb0c60((int)Item);
        if (Obj)
        {
            float Value = Source->Virtual4(0)->Class_10C3D3B0::FUN_10c3d3b0();
            Class_10E9CD90* Light = (Class_10E9CD90*)(((Class_10AA82D0*)Obj)->FUN_10aa82d0() + 0x30);
            Light->Class_10E9CD90::FUN_10bfbb80(Value);
            return 1;
        }
    }
    return 0;
}
