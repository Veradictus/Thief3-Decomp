// Game/Unsorted_109333B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10E49DFC {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int FUN_109333b0();

    char Unknown04[0x3C];
    std::vector<void*> Unknown40;
};

class Class_10933420
{
public:
    std::vector<void*>::iterator FUN_10933420(std::vector<void*>::iterator Where);

    char Unknown00[4];
    std::vector<void*> Unknown04;
};

// FUNCTION: 0x109333B0 ?FUN_109333b0@Class_10E49DFC@@UAEHXZ
int Class_10E49DFC::FUN_109333b0()
{
    return Unknown40.size();
}

// FUNCTION: 0x10933420 ?FUN_10933420@Class_10933420@@QAE?AViterator@?$vector@PAXV?$allocator@PAX@std@@@std@@V234@@Z
std::vector<void*>::iterator Class_10933420::FUN_10933420(std::vector<void*>::iterator Where)
{
    return Unknown04.erase(Where);
}
