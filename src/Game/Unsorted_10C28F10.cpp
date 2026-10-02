// Game/Unsorted_10C28F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C29000
{
public:
    int FUN_10c29000();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
    char Unknown10[0xC];
    bool Unknown1C;
};

// FUNCTION: 0x10C29000 ?FUN_10c29000@Class_10C29000@@QAEHXZ
int Class_10C29000::FUN_10c29000()
{
    if (Unknown04 > 0 && !Unknown1C)
        return *Unknown0C;
    return 0;
}
