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
