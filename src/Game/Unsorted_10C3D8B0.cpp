// Game/Unsorted_10C3D8B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10C3DD40
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E5B2C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10c3dd40(const Info_10C3DD40* In);

    char Unknown04[0x18];
    Info_10C3DD40 Unknown1C;
};

// FUNCTION: 0x10C3DD40 ?FUN_10c3dd40@Class_10E5B2C0@@UAEXPBUInfo_10C3DD40@@@Z
void Class_10E5B2C0::FUN_10c3dd40(const Info_10C3DD40* In)
{
    Unknown1C = *In;
}
