// Game/Unsorted_109E66F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Class_109E6D60_Member
{
    char Unknown00[8];
    int Unknown08;
};

class Class_109E6D60
{
public:
    bool FUN_109e6d60(int p1);

    char Unknown00[0x8C];
    Class_109E6D60_Member** Unknown8C;
};

// FUNCTION: 0x109E6D60 ?FUN_109e6d60@Class_109E6D60@@QAE_NH@Z
bool Class_109E6D60::FUN_109e6d60(int p1)
{
    return p1 == (*Unknown8C)->Unknown08;
}
