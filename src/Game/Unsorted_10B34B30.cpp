// Game/Unsorted_10B34B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7C268_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    char Unknown04[8];
};

class Class_10E7C268_Secondary
{
public:
    char Unknown00[4];
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E7C268_Secondary* A, int B, int C, int D);
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E7C268 : public Class_10E7C268_Primary, public Class_10E7C268_Secondary
{
public:
    virtual void FUN_10b35120();
};

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

class Class_1096C8D0_Field0C
{
public:
    char Unknown00[0x1C];
    int Unknown1C;
};

class Class_1096C8D0
{
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    Class_1096C8D0_Field0C* Unknown0C;
    int Unknown10;
    char Unknown14[0x10];
    int Unknown24;
};

extern Class_1096C8D0* DAT_10ff3818;

class Class_10E7C178
{
public:
    virtual ~Class_10E7C178();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10b34b80();
};

// FUNCTION: 0x10B34B80 ?FUN_10b34b80@Class_10E7C178@@UAEHXZ
int Class_10E7C178::FUN_10b34b80()
{
    int Pending;
    if (DAT_10ff3818->Unknown04 == 0)
        Pending = DAT_10ff3818->Unknown08 < UObject::GObjObjects.ArrayNum;
    else if (DAT_10ff3818->Unknown10 == DAT_10ff3818->Unknown0C->Unknown1C && DAT_10ff3818->Unknown24 == 0)
        Pending = 0;
    else
        Pending = 1;
    return !Pending;
}

// FUNCTION: 0x10B35120 ?FUN_10b35120@Class_10E7C268@@UAEXXZ
void Class_10E7C268::FUN_10b35120()
{
    DAT_10f46da0->Virtual1(this, 0x3E, DAT_10f35dec->Unknown08, -1);
}
