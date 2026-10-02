// Game/Unsorted_10A7F470.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

template <class T> class TArray
{
public:
    T* Data;
    int ArrayNum;
    int ArrayMax;
};

class UObject
{
public:
    static TArray<UObject*> GObjObjects;
};

class Class_10F3A180_Field0C
{
public:
    char Unknown00[0x1C];
    int Unknown1C;
};

class Class_10F3A180
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_10F3A180_Field0C* Unknown0C;
    int Unknown10;
    char Unknown14[0x10];
    int Unknown24;
};

extern Class_10F3A180* DAT_10f3a180;

class Class_10E6BFBC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10a7f470();
};

// FUNCTION: 0x10A7F470 ?FUN_10a7f470@Class_10E6BFBC@@UAEHXZ
int Class_10E6BFBC::FUN_10a7f470()
{
    int Pending;
    if (DAT_10f3a180->Unknown04 == 0)
        Pending = DAT_10f3a180->Unknown08 < UObject::GObjObjects.ArrayNum;
    else if (DAT_10f3a180->Unknown10 == DAT_10f3a180->Unknown0C->Unknown1C && DAT_10f3a180->Unknown24 == 0)
        Pending = 0;
    else
        Pending = 1;
    return !Pending;
}
