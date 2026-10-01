// Game/Unsorted_10C28240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10C28240
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();

    void FUN_10c28240();

    int Unknown04;
    float Unknown08;
};

class Class_10C28280_Param
{
public:
    virtual void Virtual0();
    virtual void Virtual1(void* p1, int p2);
};

class Class_10E99370
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10c28280(Class_10C28280_Param* p1);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10C28240 ?FUN_10c28240@Class_10C28240@@QAEXXZ
void Class_10C28240::FUN_10c28240()
{
    Virtual3();
    Unknown08 = (float)FUN_10c00480();
}

// FUNCTION: 0x10C28280 ?FUN_10c28280@Class_10E99370@@UAEXPAVClass_10C28280_Param@@@Z
void Class_10E99370::FUN_10c28280(Class_10C28280_Param* p1)
{
    p1->Virtual1(&Unknown08, 4);
}
