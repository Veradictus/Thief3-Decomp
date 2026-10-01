// Game/Unsorted_10A399E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10A399C0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E666A0
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
    virtual void FUN_10a399e0(const Info_10A399C0* In);

    char Unknown04[0x34];
    Info_10A399C0 Unknown38;
};

// FUNCTION: 0x10A399E0 ?FUN_10a399e0@Class_10E666A0@@UAEXPBUInfo_10A399C0@@@Z
void Class_10E666A0::FUN_10a399e0(const Info_10A399C0* In)
{
    Unknown38 = *In;
}
