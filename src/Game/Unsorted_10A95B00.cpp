// Game/Unsorted_10A95B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    bool IsPaused();
};

class Class_10E6CE78
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a95b40(int p1, int p2);
};

// FUNCTION: 0x10A95B40 ?FUN_10a95b40@Class_10E6CE78@@UAE_NHH@Z
bool Class_10E6CE78::FUN_10a95b40(int p1, int p2)
{
    return TimeManager::Instance()->IsPaused() != 0;
}
