// Game/TimeManager_12.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class TimeManager
{
public:
    void SetTimeScale(float Scale);

    float TimeScale;
};

// FUNCTION: 0x10D3ED80 ?SetTimeScale@TimeManager@@QAEXM@Z
void TimeManager::SetTimeScale(float Scale)
{
    if (DAT_10eafbdc > Scale)
        TimeScale = 0.0f;
    else
        TimeScale = Scale;
}
