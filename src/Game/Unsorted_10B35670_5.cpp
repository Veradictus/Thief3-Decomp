// Game/Unsorted_10B35670_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7C30C_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    char Unknown04[8];
};

class Class_10E7C30C_Secondary
{
public:
    char Unknown00[4];
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E7C30C_Secondary* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E7C30C : public Class_10E7C30C_Primary, public Class_10E7C30C_Secondary
{
public:
    virtual void FUN_10b359d0();
};

// FUNCTION: 0x10B359D0 ?FUN_10b359d0@Class_10E7C30C@@UAEXXZ
void Class_10E7C30C::FUN_10b359d0()
{
    DAT_10f46da0->Virtual1(this, 0x4f, -1, -1);
}
