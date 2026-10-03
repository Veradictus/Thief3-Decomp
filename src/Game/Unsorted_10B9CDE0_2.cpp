// Game/Unsorted_10B9CDE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B9CDE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();

    char Unknown04[0x3C];
    bool Unknown40;
    char Unknown41[7];
    bool Unknown48;
};

class Class_10B9CDE0
{
public:
    void FUN_10b9cde0();
    void FUN_10b9ce20();

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[4];
    Object_10B9CDE0** Unknown18;
};

// FUNCTION: 0x10B9CDE0 ?FUN_10b9cde0@Class_10B9CDE0@@QAEXXZ
void Class_10B9CDE0::FUN_10b9cde0()
{
    for (int i = Unknown10 - 1; i >= 0; i--)
    {
        Object_10B9CDE0* Item = Unknown18[i];
        if (Item->Virtual3() == 5 && !Item->Unknown48)
            Item->Unknown48 = true;
    }
}

// FUNCTION: 0x10B9CE20 ?FUN_10b9ce20@Class_10B9CDE0@@QAEXXZ
void Class_10B9CDE0::FUN_10b9ce20()
{
    for (int i = Unknown10 - 1; i >= 0; i--)
    {
        Object_10B9CDE0* Item = Unknown18[i];
        if (Item->Virtual3() == 0x23 && !Item->Unknown40)
            Item->Unknown40 = true;
    }
}
