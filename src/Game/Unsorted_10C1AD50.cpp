// Game/Unsorted_10C1AD50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E98F48
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c1ad50(Class_10E98F48* Other);
    char Unknown04[0x50];
    int Unknown54;
};

// FUNCTION: 0x10C1AD50 ?FUN_10c1ad50@Class_10E98F48@@UAEHPAV1@@Z
int Class_10E98F48::FUN_10c1ad50(Class_10E98F48* Other)
{
    return (Unknown54 - Other->Unknown54) == 0;
}
