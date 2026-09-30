// Game/Class_10E4E620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E4E590
{
public:
    Class_10E4E590(int X);

    virtual void FUN_10af3510();

    char Unknown04[0x28];
    int Unknown2C;
};

class Class_10E4E620 : public Class_10E4E590
{
public:
    Class_10E4E620();

    char Unknown30[4];
    int Unknown34;
    char Unknown38[0x24];
    int Unknown5C;
};

// FUNCTION: 0x10AEC8D0 ??0Class_10E4E620@@QAE@XZ
Class_10E4E620::Class_10E4E620() : Class_10E4E590(0)
{
    Unknown34 = 1;
    Unknown5C = 0;
}
