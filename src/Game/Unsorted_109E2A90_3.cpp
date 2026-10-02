// Game/Unsorted_109E2A90_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_109E3650
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E5B2C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void FUN_109e3650(const Info_109E3650* In);

    char Unknown04[0xC];
    Info_109E3650 Unknown10;
};

// FUNCTION: 0x109E3650 ?FUN_109e3650@Class_10E5B2C0@@UAEXPBUInfo_109E3650@@@Z
void Class_10E5B2C0::FUN_109e3650(const Info_109E3650* In)
{
    Unknown10 = *In;
}
