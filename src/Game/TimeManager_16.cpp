// Game/TimeManager_16.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    char Unknown00[0x10];
    float DeltaTime;

    float GetDeltaTime();
};

// FUNCTION: 0x10D3EDB0 ?GetDeltaTime@TimeManager@@QAEMXZ
float TimeManager::GetDeltaTime()
{
    return DeltaTime;
}
