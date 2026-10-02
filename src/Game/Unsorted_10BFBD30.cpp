// Game/Unsorted_10BFBD30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10BFBE30
{
public:
    bool FUN_10bfbe30();

    char Unknown00[4];
    float Unknown04;
    float Unknown08;
};

// FUNCTION: 0x10BFBE30 ?FUN_10bfbe30@Class_10BFBE30@@QAE_NXZ
bool Class_10BFBE30::FUN_10bfbe30()
{
    float Limit = Unknown08;
    if (FUN_10c00480() - Unknown04 > Limit)
        return true;
    return false;
}
