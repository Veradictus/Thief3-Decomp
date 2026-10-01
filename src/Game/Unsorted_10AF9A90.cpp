// Game/Unsorted_10AF9A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e74218[];

class Class_10AF4B90
{
public:
    Class_10AF4B90* FUN_10af4b90(int p1, void* p2);
};

class Class_10AF9A90
{
public:
    Class_10AF9A90* FUN_10af9a90();

    char Unknown00[0x10];
    Class_10AF4B90 Unknown10;
};

// FUNCTION: 0x10AF9A90 ?FUN_10af9a90@Class_10AF9A90@@QAEPAV1@XZ
Class_10AF9A90* Class_10AF9A90::FUN_10af9a90()
{
    Unknown10.FUN_10af4b90(4, DAT_10e74218);
    return this;
}
