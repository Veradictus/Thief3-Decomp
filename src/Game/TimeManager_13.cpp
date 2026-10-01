// Game/TimeManager_13.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    void SetMaxStep(float Step);

    float TimeScale;
    float MinStep;
    float MaxStep;
};

// FUNCTION: 0x10D3ECA0 ?SetMaxStep@TimeManager@@QAEXM@Z
void TimeManager::SetMaxStep(float Step)
{
    if (Step > MinStep)
        MaxStep = Step;
    else
        MaxStep = MinStep;
}
