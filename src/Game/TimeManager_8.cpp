// Game/TimeManager_8.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager {
public:
    char Unknown00[0x18];
    double GameTime;
    char Unknown20[0x1d];
    bool Unknown3D;

    void SetGameTime(double Time);
};

// FUNCTION: 0x10D3EC90 ?SetGameTime@TimeManager@@QAEXN@Z
void TimeManager::SetGameTime(double Time)
{
    Unknown3D = true;
    GameTime = Time;
}
