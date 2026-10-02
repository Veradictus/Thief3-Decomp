// Game/Unsorted_10B2EE60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10E7B89C
{
public:
    virtual void Virtual0();
    virtual bool FUN_10b2ee60();

    char Unknown04[8];
    float Unknown0C;
    float Unknown10;
};

// FUNCTION: 0x10B2EE60 ?FUN_10b2ee60@Class_10E7B89C@@UAE_NXZ
bool Class_10E7B89C::FUN_10b2ee60()
{
    if (Unknown0C < DAT_10eafbdc)
        return false;
    return Unknown10 >= Unknown0C ? 1 : 0;
}
