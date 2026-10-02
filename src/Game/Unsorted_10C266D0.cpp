// Game/Unsorted_10C266D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E992D4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10c266d0();

    void FUN_10c265c0();
    void FUN_10c26600();

    char Unknown04[0x30];
    bool Unknown34;
    char Unknown35[3];
    int Unknown38;
};

// FUNCTION: 0x10C266D0 ?FUN_10c266d0@Class_10E992D4@@UAEXXZ
void Class_10E992D4::FUN_10c266d0()
{
    if (!Unknown34)
    {
        if (Unknown38 > 0)
            FUN_10c265c0();
    }
    else if (Unknown38 == 0)
        FUN_10c26600();
}
