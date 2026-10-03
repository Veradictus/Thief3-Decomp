// Game/Unsorted_10A52F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A52F10
{
public:
    int FUN_10a52f10(int Value);

    char Unknown00[0xB8];
    int UnknownB8;
    char UnknownBC[4];
    int* UnknownC0;
};

extern float DAT_10eafbdc;

class Class_10A53220
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(float Value);

    void FUN_10a53220(float Delta);

    float Unknown04;
    float Unknown08;
};

// FUNCTION: 0x10A52F10 ?FUN_10a52f10@Class_10A52F10@@QAEHH@Z
int Class_10A52F10::FUN_10a52f10(int Value)
{
    int i;
    for (i = 0; i < UnknownB8; i++)
    {
        if (Value == UnknownC0[i])
            break;
    }
    if (i == UnknownB8)
        return -1;
    return i;
}

// FUNCTION: 0x10A53220 ?FUN_10a53220@Class_10A53220@@QAEXM@Z
void Class_10A53220::FUN_10a53220(float Delta)
{
    if (!(Unknown08 <= DAT_10eafbdc))
        Unknown08 -= Delta;
    else
        Virtual5(Unknown04 * Delta);
}
