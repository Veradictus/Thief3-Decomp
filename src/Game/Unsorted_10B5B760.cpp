// Game/Unsorted_10B5B760.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e82e90[];

class Class_10E81130
{
public:
    Class_10E81130* FUN_10b46080();

    void** Unknown00;
    char Unknown04[0x160];
};

class Class_10E82E90 : public Class_10E81130
{
public:
    Class_10E82E90* FUN_10b5b7b0();

    int Unknown164;
    int Unknown168[4];
    int Unknown178;
};

// FUNCTION: 0x10B5B7B0 ?FUN_10b5b7b0@Class_10E82E90@@QAEPAV1@XZ
Class_10E82E90* Class_10E82E90::FUN_10b5b7b0()
{
    FUN_10b46080();
    Unknown00 = DAT_10e82e90;
    Unknown164 = 0;
    for (int i = 0; i < 4; i++)
        Unknown168[i] = 0;
    Unknown178 = 1;
    return this;
}
