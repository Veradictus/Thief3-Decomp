// Game/Unsorted_10C63FD0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" void* memcpy(void* Dest, const void* Src, unsigned Count);

class Class_10E9CD90
{
public:
    virtual void Virtual0();
    virtual void FUN_10c63fd0(void* Dest, unsigned Count);

    char Unknown04[0x30];
    char* Unknown34;
    int Unknown38;
    int Unknown3C;
};

// FUNCTION: 0x10C63FD0 ?FUN_10c63fd0@Class_10E9CD90@@UAEXPAXI@Z
void Class_10E9CD90::FUN_10c63fd0(void* Dest, unsigned Count)
{
    memcpy(Dest, Unknown34 + Unknown3C, Count);
    Unknown3C += Count;
}
