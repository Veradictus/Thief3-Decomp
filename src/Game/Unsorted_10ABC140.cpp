// Game/Unsorted_10ABC140.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E70A50
{
public:
    Class_10E70A50();

    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10993EC0 : public Class_10E70A50
{
public:
    Class_10993EC0()
    {
        UnknownB0 = 0;
        UnknownB4 = 0;
        UnknownB8 = 0;
    }

    virtual void FUN_10adb3a0();

    char Unknown2C[0x84];
    int UnknownB0;
    int UnknownB4;
    int UnknownB8;
};

class Object_10ABD7F0
{
public:
    virtual ~Object_10ABD7F0();
};

class ASpellProjectile : public Class_10993EC0
{
public:
    virtual void FUN_10adb3a0();

    char UnknownBC[0x14];
    Object_10ABD7F0* Unknown0D0;
};

class Class_1098E330
{
public:
    void FUN_1098e330(int Id, int* Out);
};

class Class_10ABEA80 {
public:
    void FUN_10abe270(int param);
    void FUN_10abea80();
};

struct Struct_10AA3520_Member
{
    char Unknown00[0x214];
    int Unknown214;
};

struct Struct_10AA3520
{
    char Unknown00[0x08];
    Struct_10AA3520_Member* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10ABFBB0 {
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    unsigned char Unknown0c;

    Class_10ABFBB0* FUN_10abfbb0();
};

// FUNCTION: 0x10ABD7F0 ?FUN_10adb3a0@ASpellProjectile@@UAEXXZ
void ASpellProjectile::FUN_10adb3a0()
{
    if (Unknown0D0)
    {
        delete Unknown0D0;
        Unknown0D0 = 0;
    }
    Class_10993EC0::FUN_10adb3a0();
}

// FUNCTION: 0x10ABE100 ?FUN_10abe100@@YA_NPAVClass_1098E330@@@Z
bool FUN_10abe100(Class_1098E330* Obj)
{
    int Value = 0;
    Obj->FUN_1098e330(0x800863, &Value);
    return Value == 1;
}

// FUNCTION: 0x10ABE130 ?FUN_10abe130@@YA_NPAVClass_1098E330@@@Z
bool FUN_10abe130(Class_1098E330* Obj)
{
    int Value = 0;
    Obj->FUN_1098e330(0x800864, &Value);
    return Value == 1;
}

// FUNCTION: 0x10ABEA80 ?FUN_10abea80@Class_10ABEA80@@QAEXXZ
void Class_10ABEA80::FUN_10abea80()
{
    FUN_10abe270(1);
}

// FUNCTION: 0x10ABF1F0 ?FUN_10abf1f0@@YAPAHXZ
int* FUN_10abf1f0()
{
    return &DAT_10f35dec->Unknown08->Unknown214;
}

// FUNCTION: 0x10ABFBB0 ?FUN_10abfbb0@Class_10ABFBB0@@QAEPAV1@XZ
Class_10ABFBB0* Class_10ABFBB0::FUN_10abfbb0()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0c = 0;
    return this;
}
