// Game/Unsorted_10C1A960.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C1AA80
{
public:
    char Unknown00[0x2C];
    float Unknown2C;
    void FUN_10c1aa80(float param);
};

class Class_10c1aa90
{
public:
    char Unknown00[0x44];
    unsigned char Unknown44;
    void FUN_10c1aa90(unsigned char p1);
};

// FUNCTION: 0x10C1AA80 ?FUN_10c1aa80@Class_10C1AA80@@QAEXM@Z
void Class_10C1AA80::FUN_10c1aa80(float param)
{
    Unknown2C *= param;
}

// FUNCTION: 0x10C1AA90 ?FUN_10c1aa90@Class_10c1aa90@@QAEXE@Z
void Class_10c1aa90::FUN_10c1aa90(unsigned char p1)
{
    Unknown44 = p1;
}
