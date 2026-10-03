// Game/Unsorted_10ACA550_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
};

extern float DAT_10eafbdc;

extern Class_10F46DA0* DAT_10f46da0;

class Class_10ACA620
{
public:
    void FUN_10aca5b0(float A);
    void FUN_10aca620();

    char Unknown00[4];
    int Unknown04;
    float Unknown08;
};

// FUNCTION: 0x10ACA5B0 ?FUN_10aca5b0@Class_10ACA620@@QAEXM@Z
void Class_10ACA620::FUN_10aca5b0(float A)
{
    if (Unknown08 > DAT_10eafbdc)
    {
        Unknown08 -= A;
        if (Unknown08 <= DAT_10eafbdc)
        {
            Unknown08 = 0.0f;
            DAT_10f46da0->Virtual5(0xb, Unknown04, -1, 0);
        }
    }
}
