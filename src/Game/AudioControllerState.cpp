// Game/AudioControllerState.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cIntArray.h"
#include "Game/Config.h"

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10C02530;

Class_10C02530* FUN_10c02670();

void FUN_10c013c0();

class Class_10C02B90;

class AudioController {
public:
    virtual void FUN_10c047f0();
    AudioController(Class_10C02B90* Value) : Owner(Value) {}
    Class_10C02B90* Owner;
};

class Class_10C02B90 {
public:
    Class_10C02B90();
    ~Class_10C02B90();
    cIntArray Items;
    AudioController* Callback;
    cIntArray Queue;
    cIntArray Pending;
    cIntArray Active;
    bool Enabled;
};

// FUNCTION: 0x10C02720 FUN_10c02720
Class_10C02B90::Class_10C02B90() : Callback(0), Enabled(false)
{
    FUN_10c02670();
    FUN_10c013c0();
    GetAllocator()->Virtual8(0, 0);
    int Tag = 0;
    Callback = new(Tag, 0, 0, 0, 0) AudioController(this);
    GetAllocator()->Virtual9();
    int ConfigValue;
    Enabled = Config::Instance()->FUN_10910a20("Engine.Engine", "LogBarkRequests", &ConfigValue, 0);
}
