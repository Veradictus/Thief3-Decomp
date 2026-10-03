// Game/Unsorted_10C2E390_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

double FUN_10c00480();

class Class_10E9AA38
{
public:
    virtual bool FUN_10c2e500();

    char Unknown04[0x48];
    bool Unknown4C;
    char Unknown4D[0xF];
    float Unknown5C;
    float Unknown60;
};

// FUNCTION: 0x10C2E500 ?FUN_10c2e500@Class_10E9AA38@@UAE_NXZ
bool Class_10E9AA38::FUN_10c2e500()
{
    if (Unknown5C != DAT_10eafbdc)
    {
        double EndTime = Unknown5C + Unknown60;
        if (FUN_10c00480() > EndTime)
            return true;
    }
    return Unknown4C;
}
