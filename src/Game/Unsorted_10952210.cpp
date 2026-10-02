// Game/Unsorted_10952210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10952390_A
{
    char Unknown00[0x4C];
    bool Unknown4C;
};

struct Struct_10952390_B
{
    int Unknown00;
    int Unknown04;
};

class Class_10952390
{
public:
    bool FUN_10952390();

    Struct_10952390_A* Unknown00;
    Struct_10952390_B* Unknown04;
};

// FUNCTION: 0x10952390 ?FUN_10952390@Class_10952390@@QAE_NXZ
bool Class_10952390::FUN_10952390()
{
    if (Unknown04)
    {
        if (Unknown04->Unknown04 & 0x400)
            return true;
    }
    return Unknown00->Unknown4C;
}
