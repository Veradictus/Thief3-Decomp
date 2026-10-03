// Game/Unsorted_10C1AB00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BA91E0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

float FUN_10ba91e0(const Struct_10BA91E0* A, const Struct_10BA91E0* B);

class Class_10BBDC30
{
public:
    float FUN_10bbdad0(int A);
};

class Class_10BBDB40 : public Class_10BBDC30
{
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

class Class_10E98DE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c1ab00(Class_10E98DE0* Other);

    char Unknown04[4];
    Class_10DBD510* Unknown08;
    char Unknown0C[0x3C];
    Struct_10BA91E0 Unknown48;
};

// FUNCTION: 0x10C1AB00 ?FUN_10c1ab00@Class_10E98DE0@@UAEHPAV1@@Z
int Class_10E98DE0::FUN_10c1ab00(Class_10E98DE0* Other)
{
    float Limit = Unknown08->FUN_10dbd510()->FUN_10bbdad0(0x40100373) * 16.0f;
    if (FUN_10ba91e0(&Unknown48, &Other->Unknown48) < Limit)
        return 1;
    return 0;
}
