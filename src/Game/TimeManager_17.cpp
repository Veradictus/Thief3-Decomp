// Game/TimeManager_17.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    void SetMinStep(float Step);

    char Unknown00[4];
    float MinStep;
    float MaxStep;
};

// FUNCTION: 0x10D3ECD0 ?SetMinStep@TimeManager@@QAEXM@Z
void TimeManager::SetMinStep(float Step)
{
    if (Step < MaxStep)
        MinStep = Step;
    else
        MinStep = MaxStep;
}
