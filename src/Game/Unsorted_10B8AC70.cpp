// Game/Unsorted_10B8AC70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B87EC0
{
public:
    bool FUN_10b87ec0();

    char Unknown00[4];
    int Unknown04;
};

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
    virtual bool FUN_10b8ac70();

    char Unknown04[0x28];
    Class_10B87EC0* Unknown2C;
};

// FUNCTION: 0x10B8AC70 ?FUN_10b8ac70@Class_10E894C8@@UAE_NXZ
bool Class_10E894C8::FUN_10b8ac70()
{
    Class_10B87EC0* Item = Unknown2C;
    if (Item && Item->Unknown04 == 2)
        return Item->FUN_10b87ec0();
    return false;
}
