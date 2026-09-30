// Game/Unsorted_10A1E620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10a1e620(void* Object);

void FUN_10a1eaa0(void* Object);

class Class_10A1ED10
{
public:
    char Unknown00[0x288];
    void* Unknown288;
};

// FUNCTION: 0x10A1ED10 ?FUN_10a1ed10@@YAXPAVClass_10A1ED10@@@Z
void FUN_10a1ed10(Class_10A1ED10* Owner)
{
    void* Object = Owner->Unknown288;
    if (Object)
    {
        FUN_10a1e620(Object);
        FUN_10a1eaa0(Object);
    }
}
