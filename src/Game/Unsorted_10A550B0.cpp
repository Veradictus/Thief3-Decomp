// Game/Unsorted_10A550B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e68738[];

extern void* DAT_10e7edb8[];

class Class_10E69080
{
public:
    Class_10E69080();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0xB4];
};

struct Struct_10A56130
{
    Struct_10A56130() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E68738 : public Class_10E69080
{
public:
    Class_10E68738* FUN_10a56130();

    int Unknown1D0;
    char Unknown1D4;
    Struct_10A56130 Unknown1D8;
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E684A8 : public Class_10E67FD0
{
public:
    Class_10E684A8();

    virtual ~Class_10E684A8();

    bool Unknown118;
    bool Unknown119;
    int Unknown11C;
    bool Unknown120;
    FArray Unknown124;
    int Unknown130;
    int Unknown134;
    int Unknown138;
    int Unknown13C;
    int Unknown140;
    bool Unknown144;
    int Unknown148;
};

// FUNCTION: 0x10A55150 ??0Class_10E684A8@@QAE@XZ
Class_10E684A8::Class_10E684A8()
    : Unknown118(false), Unknown119(false), Unknown11C(0), Unknown120(false), Unknown130(0), Unknown134(0),
      Unknown138(0), Unknown13C(0), Unknown140(0), Unknown144(false), Unknown148(0)
{
}

// FUNCTION: 0x10A55FF0 ??_GClass_10E684A8@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10A55150's definition in this unit.

// FUNCTION: 0x10A56130 ?FUN_10a56130@Class_10E68738@@QAEPAV1@XZ
Class_10E68738* Class_10E68738::FUN_10a56130()
{
    this->Class_10E69080::Class_10E69080();
    Unknown00 = DAT_10e68738;
    Unknown118 = DAT_10e7edb8;
    Unknown1D0 = 0;
    Unknown1D4 = 0;
    Unknown1D8.Struct_10A56130::Struct_10A56130();
    return this;
}
