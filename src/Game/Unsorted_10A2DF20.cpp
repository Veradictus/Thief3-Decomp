// Game/Unsorted_10A2DF20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_10a2e900(void* p1);

class Class_10A2EE30
{
public:
    Class_10A2EE30* FUN_10a2ee30();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

class Class_10A2E430
{
public:
    bool FUN_10a2e430(unsigned Mask);

    unsigned Unknown00;
};

extern void* DAT_10f39f34;

// FUNCTION: 0x10A2E430 ?FUN_10a2e430@Class_10A2E430@@QAE_NI@Z
bool Class_10A2E430::FUN_10a2e430(unsigned Mask)
{
    if (Unknown00 == 0xFFFFFFFF)
        return true;
    if (Unknown00 >= 32)
        return false;
    return (Mask & (1 << Unknown00)) != 0;
}

// FUNCTION: 0x10A2E4B0 ?FUN_10a2e4b0@@YAXXZ
void FUN_10a2e4b0()
{
    if (DAT_10f39f34)
    {
        delete DAT_10f39f34;
        DAT_10f39f34 = 0;
    }
}

// FUNCTION: 0x10A2ED30 ?FUN_10a2ed30@@YAHPAX@Z
int FUN_10a2ed30(void* p1)
{
    if (!p1)
        return -1;
    return FUN_10a2e900(p1);
}

// FUNCTION: 0x10A2EE30 ?FUN_10a2ee30@Class_10A2EE30@@QAEPAV1@XZ
Class_10A2EE30* Class_10A2EE30::FUN_10a2ee30()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = -1;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    return this;
}
