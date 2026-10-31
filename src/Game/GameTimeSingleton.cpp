// Game/GameTimeSingleton.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10905A90_Member.h"

// Allocation-only view: original allocation is 0x44 and constructor stores at +0x40.
class TimeManager
{
public:
    TimeManager();
    static TimeManager* Instance();
private:
    static TimeManager* GSingleton;
    char Unknown00[0x44];
};

Class_10905A90_Member* GetAllocator();

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x10D3EBE0 ?Instance@TimeManager@@SAPAV1@XZ
TimeManager* TimeManager::Instance()
{
    if (!GSingleton)
    {
        GetAllocator()->Virtual8(0, 0);
        GSingleton = new(0, 0, 0, 0, 0) TimeManager;
        GetAllocator()->Virtual9();
    }
    return GSingleton;
}
