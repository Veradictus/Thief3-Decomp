// Game/Unsorted_10B22020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3ED20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

class Class_10B228E0
{
public:
    bool FUN_10b228e0();

    char Unknown00[0x90];
    Class_10B3ED20* Unknown90;
};

// FUNCTION: 0x10B228E0 ?FUN_10b228e0@Class_10B228E0@@QAE_NXZ
bool Class_10B228E0::FUN_10b228e0()
{
    if (Unknown90->Virtual4() != 0x15 && Unknown90->Virtual4() != 0x16)
        return true;
    return false;
}
