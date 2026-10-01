// Game/Unsorted_1091E350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E499F4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual bool FUN_1091e350();

    char Unknown04[0x54];
    unsigned int : 3;
    unsigned int Unknown58Bit3 : 1;
    unsigned int : 2;
    unsigned int Unknown58Bit6 : 1;
};

// FUNCTION: 0x1091E350 ?FUN_1091e350@Class_10E499F4@@UAE_NXZ
bool Class_10E499F4::FUN_1091e350()
{
    if (Unknown58Bit3 || Unknown58Bit6)
        return false;
    return true;
}
