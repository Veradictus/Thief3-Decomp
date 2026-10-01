// Game/Unsorted_109E3A10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5B7C8 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_109e3c60(int p1);

    char Unknown04[0x90];
    int Unknown94;
};

class Class_109E3C40
{
public:
    int FUN_109e3c40();

    char Unknown00[0x218];
    int Unknown218;
    int Unknown21C;
};

// FUNCTION: 0x109E3C40 ?FUN_109e3c40@Class_109E3C40@@QAEHXZ
int Class_109E3C40::FUN_109e3c40()
{
    if (Unknown21C > 0 || Unknown218 > 0)
        return 1;
    return 0;
}

// FUNCTION: 0x109E3C60 ?FUN_109e3c60@Class_10E5B7C8@@UAE_NH@Z
bool Class_10E5B7C8::FUN_109e3c60(int p1)
{
    Unknown94 = p1;
    return true;
}
