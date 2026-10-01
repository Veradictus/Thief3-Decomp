// Game/Unsorted_1098E590.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

inline void* operator new(unsigned int, void* Ptr)
{
    return Ptr;
}

class Class_10E70A50
{
public:
    Class_10E70A50();

    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10993EC0 : public Class_10E70A50
{
public:
    Class_10993EC0()
    {
        UnknownB0 = 0;
        UnknownB4 = 0;
        UnknownB8 = 0;
    }

    virtual void FUN_10adb3a0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class ASpecialOptions : public Class_10993EC0
{
public:
    ASpecialOptions();
};

// FUNCTION: 0x1098E590 ?FUN_1098e590@@YAXPAX@Z
void FUN_1098e590(void* Memory)
{
    new (Memory) ASpecialOptions();
}
