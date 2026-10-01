// Game/Unsorted_10933200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_109331D0;

class Class_10933230
{
public:
    void FUN_10933230();

    char Unknown00[0x14];
    unsigned char Unknown14;
};

class Class_10E49D44
{
public:
    virtual int FUN_10932fa0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10933200(unsigned int Index);

    int Unknown04;
    Object_109331D0* Unknown08;
    unsigned int Unknown0C;
    Class_10933230** Unknown10;
};

// FUNCTION: 0x10933200 ?FUN_10933200@Class_10E49D44@@UAEHI@Z
int Class_10E49D44::FUN_10933200(unsigned int Index)
{
    if (Index >= Unknown0C)
        return 0x80070057;
    Class_10933230* Item = Unknown10[Index];
    if (!(Item->Unknown14 & 1))
        return 0x8004071e;
    Item->FUN_10933230();
    return 0;
}
