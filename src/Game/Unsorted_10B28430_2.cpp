// Game/Unsorted_10B28430_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7AD54
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10b289c0(float Delta);

    void FUN_10b289f0(bool A);

    char Unknown04[8];
    float Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10B289C0 ?FUN_10b289c0@Class_10E7AD54@@UAEXM@Z
void Class_10E7AD54::FUN_10b289c0(float Delta)
{
    Unknown0C += Delta;
    if (Unknown0C > (float)Unknown10)
        FUN_10b289f0(true);
}
