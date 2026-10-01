// Game/TimeManager.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    bool IsPaused();

    char Unknown00[0x3e];
    bool Paused;
};

// FUNCTION: 0x10D3ED40 ?IsPaused@TimeManager@@QAE_NXZ
bool TimeManager::IsPaused()
{
    return Paused;
}
