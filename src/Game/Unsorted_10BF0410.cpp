// Game/Unsorted_10BF0410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10AA82D0_Result
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int Virtual5();
};

class Class_10BF08D0 : public Class_10BC4160
{
public:
    void FUN_10bf08d0();

    char Unknown04[0x134];
    bool Unknown138;
};

// FUNCTION: 0x10BF08D0 ?FUN_10bf08d0@Class_10BF08D0@@QAEXXZ
void Class_10BF08D0::FUN_10bf08d0()
{
    Class_10AA82D0_Result* P = (Class_10AA82D0_Result*)FUN_10bc4160()->FUN_10aa82d0();
    if (!P || P->Virtual5() == 0x11)
        Unknown138 = true;
}
