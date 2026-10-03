// Game/Unsorted_10C380E0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10c380d0_Member
{
public:
    virtual void Virtual0() = 0;
    virtual void Virtual1() = 0;
    virtual void Virtual2() = 0;
    virtual void Virtual3() = 0;
    virtual void Virtual4() = 0;
    virtual void Virtual5() = 0;
    virtual void Virtual6() = 0;
    virtual void Virtual7() = 0;
    virtual void Virtual8() = 0;
    virtual void Virtual9() = 0;
    virtual void Virtual10() = 0;
    virtual void Virtual11() = 0;
    virtual void Virtual12() = 0;
    virtual void Virtual13() = 0;
    virtual void Virtual14() = 0;
    virtual void Virtual15() = 0;
    virtual void Virtual16() = 0;
    virtual void Virtual17() = 0;
    virtual void Virtual18() = 0;
    virtual void Virtual19() = 0;
    virtual void Virtual20() = 0;
    virtual void Virtual21() = 0;
    virtual void Virtual22() = 0;
    virtual void Virtual23() = 0;
    virtual void Virtual24() = 0;
    virtual void Virtual25() = 0;
    virtual void Virtual26() = 0;
    virtual void Virtual27() = 0;
    virtual void Virtual28() = 0;
    virtual void Virtual29() = 0;
    virtual void Virtual30() = 0;
    virtual void Virtual31() = 0;
    virtual void Virtual32() = 0;
    virtual void Virtual33() = 0;
    virtual void Virtual34() = 0;
    virtual void Virtual35() = 0;
    virtual void Virtual36() = 0;
    virtual void Virtual37() = 0;
    virtual void Virtual38() = 0;
    virtual void Virtual39() = 0;
    virtual void Virtual40() = 0;
    virtual void Virtual41() = 0;
    virtual void Virtual42() = 0;
    virtual void Virtual43() = 0;
    virtual void Virtual44() = 0;
};

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a20(const Struct_10C05A50* A, const Struct_10C05A50* B);

struct Struct_10C3D0A0
{
    char Unknown00[0x2C];
    Struct_10C05A50 Unknown2C;
};

class Class_10C270C0
{
public:
    virtual void Virtual0();

    Class_10c7d570* FUN_10c270c0();

    Class_10c380d0_Member* Unknown04;
};

class Class_10E9AEC8 : public Class_10C270C0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10c38210();

    char Unknown08[0x50];
    unsigned char Unknown58;
    Struct_10C05A50 Unknown5C;
    char Unknown64[4];
    float Unknown68;
};

// FUNCTION: 0x10C38210 ?FUN_10c38210@Class_10E9AEC8@@UAEXXZ
void Class_10E9AEC8::FUN_10c38210()
{
    if (!Unknown58)
    {
        Struct_10C3D0A0* Actor = (Struct_10C3D0A0*)FUN_10c270c0()->FUN_10c7d570();
        if (FUN_10c05a20(&Unknown5C, &Actor->Unknown2C) > Unknown68)
        {
            Unknown58 = 1;
            Unknown04->Virtual44();
        }
    }
}
