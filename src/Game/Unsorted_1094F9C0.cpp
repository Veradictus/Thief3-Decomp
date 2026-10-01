// Game/Unsorted_1094F9C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" __declspec(dllimport) void __stdcall _BinkSetVolume(void* Bink, unsigned Track, int Volume);

void FUN_109e29f0(float Value, int* Out);

struct Struct_10950310
{
    void* Bink;
};

class Class_10950310
{
public:
    void FUN_10950310(float Volume);

    Struct_10950310* Unknown00;
};

// FUNCTION: 0x10950310 ?FUN_10950310@Class_10950310@@QAEXM@Z
void Class_10950310::FUN_10950310(float Volume)
{
    FUN_109e29f0(Volume, (int*)&Volume);
    _BinkSetVolume(Unknown00->Bink, 0, *(int*)&Volume);
}
