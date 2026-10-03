// Game/Unsorted_10C64030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e9cdec[];

class Class_10C64900_Inner
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual Class_109081E0 Virtual2();
};

struct Struct_10C64900
{
    int Unknown00;
    Class_10C64900_Inner* Unknown04;
};

class Class_10C64900
{
public:
    Class_109081E0 FUN_10c64900();

    char Unknown00[8];
    Struct_10C64900* Unknown08;
};

// FUNCTION: 0x10C64900 ?FUN_10c64900@Class_10C64900@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10C64900::FUN_10c64900()
{
    if (Unknown08->Unknown04)
        return Unknown08->Unknown04->Virtual2();
    return Class_109081E0(DAT_10e9cdec);
}
