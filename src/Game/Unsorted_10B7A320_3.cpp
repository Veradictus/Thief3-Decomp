// Game/Unsorted_10B7A320_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7B910
{
public:
    Class_10B7B910* FUN_10b7b910();

    int Field00;
};

class Class_10E6AEA0
{
public:
    Class_10E6AEA0();
    virtual ~Class_10E6AEA0();

    char Unknown04[0x14C];
};

class Class_10E822B0 : public Class_10E6AEA0
{
public:
    Class_10E822B0();
    virtual ~Class_10E822B0();

    Class_10B7B910 Unknown150;
};

// FUNCTION: 0x10B7A6A0 ??0Class_10E822B0@@QAE@XZ
Class_10E822B0::Class_10E822B0()
{
    Unknown150.FUN_10b7b910();
}
