// Game/Unsorted_10C1AC60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E98EB8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c1ac60(Class_10E98EB8* Other);

    char Unknown04[0x20];
    float Unknown24;
};

// FUNCTION: 0x10C1AC60 ?FUN_10c1ac60@Class_10E98EB8@@UAEHPAV1@@Z
int Class_10E98EB8::FUN_10c1ac60(Class_10E98EB8* Other)
{
    if (Unknown24 + 0.3f > Other->Unknown24)
        return 1;
    return 0;
}
