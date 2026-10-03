// Game/TimeManager_19.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class TimeManager
{
public:
    void SetPaused(bool Pause);

    char Unknown00[0x14];
    float Unknown14;
    char Unknown18[0x26];
    bool Paused;
};

// FUNCTION: 0x10D3ED00 ?SetPaused@TimeManager@@QAEX_N@Z
void TimeManager::SetPaused(bool Pause)
{
    Unknown14 = -1.0f;
    if (Paused != Pause)
    {
        Paused = Pause;
        if (Pause)
            DAT_10f46da0->Virtual5(0x74, 0, 0, 0);
        else
            DAT_10f46da0->Virtual5(0x75, 0, 0, 0);
    }
}
