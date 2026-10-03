// Game/Unsorted_10B80650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e89210[];

class Class_10E893B0
{
public:
    Class_10E893B0* FUN_10b87610(int A);

    void** Unknown00;
    char Unknown04[0x78];
};

struct Struct_10B81920
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E89210 : public Class_10E893B0
{
public:
    Class_10E89210* FUN_10b81920();

    int Unknown7C;
    int Unknown80;
    int Unknown84;
    int Unknown88;
    int Unknown8C;
    int Unknown90;
    int Unknown94;
    int Unknown98;
    int Unknown9C;
    int UnknownA0[8];
    int UnknownC0;
    int UnknownC4;
    Struct_10B81920 UnknownC8[5];
    bool Unknown104;
    bool Unknown105;
    int Unknown108;
    int Unknown10C;
    int Unknown110;
    bool Unknown114;
    int Unknown118;
    int Unknown11C;
    bool Unknown120;
    int Unknown124;
};

// FUNCTION: 0x10B81920 ?FUN_10b81920@Class_10E89210@@QAEPAV1@XZ
Class_10E89210* Class_10E89210::FUN_10b81920()
{
    FUN_10b87610(2);
    Unknown00 = DAT_10e89210;
    Unknown7C = 0;
    Unknown80 = 0;
    Unknown84 = 0;
    Unknown88 = 0;
    Unknown8C = 0;
    Unknown90 = 0;
    Unknown94 = 0;
    Unknown98 = 0;
    Unknown9C = 0;
    for (int i = 0; i < 8; i++)
        UnknownA0[i] = 0;
    UnknownC0 = 2;
    UnknownC4 = 0;
    for (int j = 0; j < 5; j++)
    {
        UnknownC8[j].Unknown00 = 0;
        UnknownC8[j].Unknown04 = 0;
        UnknownC8[j].Unknown08 = 0;
    }
    Unknown104 = false;
    Unknown105 = false;
    Unknown108 = 0;
    Unknown10C = 0;
    Unknown110 = 0;
    Unknown114 = false;
    Unknown118 = 0;
    Unknown11C = 0;
    Unknown120 = true;
    Unknown124 = 0;
    return this;
}
