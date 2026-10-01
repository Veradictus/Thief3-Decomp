// Game/Unsorted_10919490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10d20ec0(double A);

class Class_10940970
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_1093E930
{
public:
    void FUN_1093e550();
};

class Class_1093EDB0
{
public:
    void FUN_1093edb0();
};

class Class_10937730
{
public:
    void FUN_10937730();
};

extern Class_10940970* DAT_10f2c8e4;

extern Class_1093E930* DAT_10f340ac;

extern Class_1093EDB0* DAT_10f340c0;

extern Class_10937730* DAT_10f31bdc;

// FUNCTION: 0x10919610 ?FUN_10919610@@YAXXZ
void FUN_10919610()
{
    if (DAT_10f2c8e4)
        DAT_10f2c8e4->Virtual2();
    DAT_10f340ac->FUN_1093e550();
    DAT_10f340c0->FUN_1093edb0();
    DAT_10f31bdc->FUN_10937730();
}

// FUNCTION: 0x10919B10 ?FUN_10919b10@@YAMM@Z
float FUN_10919b10(float A)
{
    int I = (int)(A * 100.0f);
    return FUN_10d20ec0((float)I * 0.01f);
}
