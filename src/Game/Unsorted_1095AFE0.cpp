// Game/Unsorted_1095AFE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1095B070
{
public:
    int FUN_1095b070();

    float Unknown00;
    char Unknown04[4];
    int* Unknown08;
    int Unknown0C;
    float Unknown10;
};

class TimeManager
{
public:
    static TimeManager* Instance();
    bool IsPaused();
    double GetGameTime();
};

double FUN_1095af80();

class Class_1095B040
{
public:
    void FUN_1095b040(int A);

    float Unknown00;
};

// FUNCTION: 0x1095B040 ?FUN_1095b040@Class_1095B040@@QAEXH@Z
void Class_1095B040::FUN_1095b040(int A)
{
    if (TimeManager::Instance()->IsPaused())
        Unknown00 = FUN_1095af80();
    else
        Unknown00 = TimeManager::Instance()->GetGameTime();
}

// FUNCTION: 0x1095B070 ?FUN_1095b070@Class_1095B070@@QAEHXZ
int Class_1095B070::FUN_1095b070()
{
    if (!Unknown08)
        return 0;
    return Unknown08[(int)(Unknown10 * Unknown00) % Unknown0C];
}
