// Game/Unsorted_10A37820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A37860
{
    char Unknown00[0xC];
    int Unknown0C;
    char Unknown10[0x20];
    float Unknown30;
};

class Object_10A37860
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual Struct_10A37860* Virtual4();
};

class Object_10A37820
{
public:
    virtual void Virtual0();
    virtual Object_10A37860* Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual bool Virtual4();
};

class Class_10A37860
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(bool A);
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual Object_10A37820* Virtual12();

    void FUN_10a37820();
    bool FUN_10a37860();

    char Unknown04[0x20];
    int Unknown24;
};

// FUNCTION: 0x10A37820 ?FUN_10a37820@Class_10A37860@@QAEXXZ
void Class_10A37860::FUN_10a37820()
{
    Object_10A37820* Object = Virtual12();
    if (Object && Object->Virtual4())
        return;
    if (!Unknown24)
        Virtual3(true);
    else
        Virtual3(false);
}
