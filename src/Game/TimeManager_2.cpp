// Game/TimeManager_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    char Unknown00[0x18];
    double GameTime;

    double GetGameTime();
};

// FUNCTION: 0x10D3EC80 ?GetGameTime@TimeManager@@QAENXZ
double TimeManager::GetGameTime()
{
    return GameTime;
}
