// Game/Unsorted_10AA8060_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10d3d990(void* Reader, int* Out);

class Class_10E6C170
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10aa8060(void* Reader, int Version, int Flag);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10AA8060 ?FUN_10aa8060@Class_10E6C170@@UAEXPAXHH@Z
void Class_10E6C170::FUN_10aa8060(void* Reader, int Version, int Flag)
{
    if (Flag == 0)
        FUN_10d3d990(Reader, &Unknown08);
}
