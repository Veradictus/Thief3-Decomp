// Game/Class_10CF37A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Entry_10CF37A0
{
    int Unknown00;
    int Unknown04;
};

class Class_10CF37A0
{
public:
    void FUN_10cf37a0(int Index, int B, int C);

    char Unknown00[0x20];
    Entry_10CF37A0 Unknown20[8];
    int Unknown60;
    int Unknown64;
    char Unknown68;
};

// FUNCTION: 0x10CF37A0 ?FUN_10cf37a0@Class_10CF37A0@@QAEXHHH@Z
void Class_10CF37A0::FUN_10cf37a0(int Index, int B, int C)
{
    Unknown68 = 0;
    Unknown20[Index] = Unknown20[Unknown64 - 1];
    Unknown64--;
}
