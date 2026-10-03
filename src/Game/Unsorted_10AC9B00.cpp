// Game/Unsorted_10AC9B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    float FUN_10d3edc0();
};

class Class_10ACA3E0
{
public:
    void FUN_10aca3e0(float Time);
    void FUN_10aca180(void* Elem, float Time);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    void** Unknown0C;
};

// FUNCTION: 0x10ACA3E0 ?FUN_10aca3e0@Class_10ACA3E0@@QAEXM@Z
void Class_10ACA3E0::FUN_10aca3e0(float Time)
{
    Time += TimeManager::Instance()->FUN_10d3edc0();
    for (int i = 0; i < Unknown04; i++)
        FUN_10aca180(Unknown0C[i], Time);
}
