// Game/Unsorted_109394D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10E49E50 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int FUN_10939680();

    char Unknown04[0x1C];
    std::vector<void*> Unknown20;
};

// FUNCTION: 0x10939680 ?FUN_10939680@Class_10E49E50@@UAEHXZ
int Class_10E49E50::FUN_10939680()
{
    return Unknown20.size();
}
