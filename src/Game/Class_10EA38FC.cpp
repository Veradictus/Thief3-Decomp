// Game/Class_10EA38FC.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10CB3DD0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10EA38FC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void FUN_10cb3dd0(int A, const Info_10CB3DD0* In);

    char Unknown04[0x8];
    int Unknown0C;
    int Unknown10;
    char Unknown14[0x4];
    int Unknown18;
};

// FUNCTION: 0x10CB3DD0 ?FUN_10cb3dd0@Class_10EA38FC@@UAEXHPBUInfo_10CB3DD0@@@Z
void Class_10EA38FC::FUN_10cb3dd0(int A, const Info_10CB3DD0* In)
{
    Unknown0C -= In->Unknown04;
    Unknown10 -= In->Unknown08;
    Unknown18 -= In->Unknown0C;
}
