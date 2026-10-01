// Game/Unsorted_10C00490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    float GetDeltaTime();
};

// FUNCTION: 0x10C00490 ?FUN_10c00490@@YAMXZ
float FUN_10c00490()
{
    float DeltaTime = TimeManager::Instance()->GetDeltaTime();
    return DeltaTime;
}
