// Game/Unsorted_1094DFF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10951730
{
public:
    void FUN_10951730(int A);
};

class Class_10924100
{
public:
    char Unknown00[0x2C];
    int Unknown2C;
};

class WindowManager
{
public:
    char Unknown00[0xA0];
    int UnknownA0;
};

extern Class_10924100* DAT_10f2c740;

extern WindowManager* GWindowManager;

extern void (*DAT_10f2c748)(int);

class Class_10E4AB88
{
public:
    virtual void Virtual0();
    virtual void FUN_1094dff0(int A);

    char Unknown04[0x50];
    int Unknown54;
    char Unknown58[8];
    int Unknown60;
    char Unknown64[0x4C];
    Class_10951730* UnknownB0;
    char UnknownB4[0xB0];
    int Unknown164;
};

// FUNCTION: 0x1094DFF0 ?FUN_1094dff0@Class_10E4AB88@@UAEXH@Z
void Class_10E4AB88::FUN_1094dff0(int A)
{
    if (Unknown164 != DAT_10f2c740->Unknown2C || GWindowManager->UnknownA0)
    {
        Unknown60 |= 4;
        DAT_10f2c748(Unknown54);
        Unknown164 = DAT_10f2c740->Unknown2C;
        Class_10951730* P = UnknownB0;
        if (P)
            P->FUN_10951730(A);
    }
}
