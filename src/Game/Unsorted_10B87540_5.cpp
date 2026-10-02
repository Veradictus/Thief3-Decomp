// Game/Unsorted_10B87540_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B8CF10
{
public:
    void FUN_10b8cf10();

    char Unknown00[0x19];
    bool Unknown19;
};

class Class_10E893B0
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
    virtual void FUN_10b87e80();

    char Unknown04[0x74];
    Class_10B8CF10* Unknown78;
};

// FUNCTION: 0x10B87E80 ?FUN_10b87e80@Class_10E893B0@@UAEXXZ
void Class_10E893B0::FUN_10b87e80()
{
    Class_10B8CF10* Item = Unknown78;
    if (Item && Item->Unknown19)
        Item->FUN_10b8cf10();
}
