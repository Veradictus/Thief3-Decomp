// Game/Unsorted_10A84E60_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A37700;

struct Struct_10AA3520
{
    char Unknown00[0x10];
    Class_10A37700* Unknown10;
};

extern Struct_10AA3520* DAT_10f35dec;

class Object_10A84E60
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10A37700* A);
    virtual bool Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
};

class Class_10A84E60
{
public:
    void FUN_10a84e60();

    char Unknown00[0x20];
    Object_10A84E60* Unknown20;
};

// FUNCTION: 0x10A84E60 ?FUN_10a84e60@Class_10A84E60@@QAEXXZ
void Class_10A84E60::FUN_10a84e60()
{
    if (!Unknown20->Virtual2())
    {
        Unknown20->Virtual1(DAT_10f35dec->Unknown10);
        Unknown20->Virtual6();
    }
}
