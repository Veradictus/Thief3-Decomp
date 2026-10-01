// Game/Unsorted_10994BF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

inline void* operator new(unsigned int, void* Ptr)
{
    return Ptr;
}

class AAmbientLightVolume
{
public:
    AAmbientLightVolume();
};

// FUNCTION: 0x10994BF0 ?FUN_10994bf0@@YAXPAX@Z
void FUN_10994bf0(void* Memory)
{
    new (Memory) AAmbientLightVolume();
}
