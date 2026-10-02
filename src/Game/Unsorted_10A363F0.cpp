// Game/Unsorted_10A363F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FString
{
public:
    int FUN_10da91a0();
};

extern int DAT_10f39fe4;

extern FString DAT_10f39ff4;

extern FString DAT_10f3a000;

// FUNCTION: 0x10A36BA0 ?FUN_10a36ba0@@YA_NXZ
bool FUN_10a36ba0()
{
    if (DAT_10f39fe4 != 0)
    {
        if (DAT_10f3a000.FUN_10da91a0() != 0)
            return true;
        if (DAT_10f39ff4.FUN_10da91a0() != 0)
            return true;
    }
    return false;
}
