// Game/Unsorted_10BFF760_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    double GetGameTime();
};

// FUNCTION: 0x10C00480 ?FUN_10c00480@@YANXZ
double FUN_10c00480()
{
    double GameTime = TimeManager::Instance()->GetGameTime();
    return GameTime;
}
