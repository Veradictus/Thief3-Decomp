// Game/Unsorted_10932FB0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memset(void*, int, unsigned);

class Object_109331D0;

struct Data_10932FB0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10933230
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

    char Unknown04[0xC];
    Data_10932FB0 Unknown10;
};

class Class_10E49D44
{
public:
    virtual int FUN_10932fa0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10932fb0(unsigned int Index, Data_10932FB0* Out);
    virtual void Virtual6();
    virtual int FUN_10933200(unsigned int Index);
    virtual void Virtual8();
    virtual void Virtual9();
    virtual int FUN_10933140();

    int Unknown04;
    Object_109331D0* Unknown08;
    unsigned int Unknown0C;
    Class_10933230** Unknown10;
};

// FUNCTION: 0x10932FB0 ?FUN_10932fb0@Class_10E49D44@@UAEHIPAUData_10932FB0@@@Z
int Class_10E49D44::FUN_10932fb0(unsigned int Index, Data_10932FB0* Out)
{
    if (!Out)
        return 0x80070057;
    if (Index >= Unknown0C)
    {
        memset(Out, 0, sizeof(*Out));
        return 0x80070057;
    }
    *Out = Unknown10[Index]->Unknown10;
    return 0;
}
