// Game/Class_10E81620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e81620[];

class Class_10B3ACB0
{
public:
    void FUN_10b3acb0();

    void** Unknown00;
    char Unknown04[0x0C];
};

class Class_10E81620 : public Class_10B3ACB0
{
public:
    Class_10E81620* FUN_10b4fc90();

    float Unknown10;
    char Unknown14;
    float Unknown18;
};

// FUNCTION: 0x10B4FC90 ?FUN_10b4fc90@Class_10E81620@@QAEPAV1@XZ
Class_10E81620* Class_10E81620::FUN_10b4fc90()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e81620;
    Unknown10 = 0.33f;
    Unknown14 = 0;
    Unknown18 = 10012.444f;
    return this;
}
