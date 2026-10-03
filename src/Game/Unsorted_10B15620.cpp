// Game/Unsorted_10B15620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    double GetGameTime();
};

bool FUN_10abc140();

class Class_10B15620
{
public:
    bool FUN_10b15620();

    char Unknown00[0x268];
    double Unknown268;
};

// FUNCTION: 0x10B15620 ?FUN_10b15620@Class_10B15620@@QAE_NXZ
bool Class_10B15620::FUN_10b15620()
{
    bool Result = FUN_10abc140();
    Result &= TimeManager::Instance()->GetGameTime() - Unknown268 > 3.0;
    return Result;
}
