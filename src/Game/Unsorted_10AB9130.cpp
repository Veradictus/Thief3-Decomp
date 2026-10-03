// Game/Unsorted_10AB9130.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5BBE0
{
public:
    Class_10E5BBE0();

    virtual ~Class_10E5BBE0();

    char Unknown04[0xD4];
};

struct Struct_10ABA050
{
    Struct_10ABA050()
    {
        Unknown00 = 0;
        Unknown04 = 0;
        Unknown08 = 0;
        Unknown0C = 0;
        Unknown14 = 0;
        Unknown18 = 0;
        Unknown1C = 0;
    }

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    char Unknown1C;
};

class Class_10E6F3F4 : public Class_10E5BBE0
{
public:
    Class_10E6F3F4();

    virtual ~Class_10E6F3F4();

    int UnknownD8;
    int UnknownDC;
    int UnknownE0;
    int UnknownE4;
    int UnknownE8;
    int UnknownEC;
    int UnknownF0;
    int UnknownF4;
    int UnknownF8;
    int UnknownFC;
    int Unknown100;
    int Unknown104;
    int Unknown108;
    int Unknown10C;
    int Unknown110;
    int Unknown114;
    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    int Unknown134;
    int Unknown138;
    int Unknown13C;
    int Unknown140;
    int Unknown144;
    Struct_10ABA050 Unknown148;
};

class Class_10AF7F80
{
public:
    const char* FUN_10af7f80();
};

struct Struct_10AB9D40
{
    char Unknown00[0x24];
    Class_10AF7F80 Unknown24;
    char Unknown25[0x1B];
    int Unknown40;
};

extern char DAT_10e6b668[];

int FUN_10af3690(const char* A, const char* B);

class Class_10AB9D40
{
public:
    void FUN_10ab9a60(int A, Struct_10AB9D40* B, int C);
    void FUN_10ab9d40(int A, Struct_10AB9D40* B, int C);
};

class Object_10AB9FF0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10AB9FF0
{
public:
    Class_10AB9FF0* FUN_10ab9ff0(Class_10AB9FF0* Other);

    Object_10AB9FF0* Unknown00;
};

class Class_10E67938
{
public:
    Class_10E67938();
    virtual void FUN_10ab9d90(int Type, int A, int B, int C);
    virtual ~Class_10E67938();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a4c4d0(int A);
    virtual void Virtual7();
};

class Class_10AB90F0
{
public:
    Class_10AB90F0() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10AB90F0();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E6F30C : public Class_10E67938
{
public:
    Class_10E6F30C();
    virtual ~Class_10E6F30C();

    virtual void FUN_10ab9d90(int Type, int A, int B, int C);

    void FUN_10ab85a0();

    Class_10AB90F0 Unknown04;
    int Unknown10;
    int Unknown14;
};

// FUNCTION: 0x10AB9130 ??0Class_10E6F30C@@QAE@XZ
Class_10E6F30C::Class_10E6F30C()
    : Unknown10(0), Unknown14(0)
{
    FUN_10ab85a0();
}

// FUNCTION: 0x10AB9D40 ?FUN_10ab9d40@Class_10AB9D40@@QAEXHPAUStruct_10AB9D40@@H@Z
void Class_10AB9D40::FUN_10ab9d40(int A, Struct_10AB9D40* B, int C)
{
    Class_10AF7F80* Name = B->Unknown40 ? &B->Unknown24 : 0;
    if (FUN_10af3690(Name->FUN_10af7f80(), DAT_10e6b668) == 0)
        FUN_10ab9a60(A, B, C);
}

// FUNCTION: 0x10AB9FF0 ?FUN_10ab9ff0@Class_10AB9FF0@@QAEPAV1@PAV1@@Z
Class_10AB9FF0* Class_10AB9FF0::FUN_10ab9ff0(Class_10AB9FF0* Other)
{
    Object_10AB9FF0* Old = Unknown00;
    Unknown00 = Other->Unknown00;
    if (Unknown00)
        Unknown00->Virtual1();
    if (Old)
        Old->Virtual2();
    return this;
}

// FUNCTION: 0x10ABA050 ??0Class_10E6F3F4@@QAE@XZ
Class_10E6F3F4::Class_10E6F3F4()
    : UnknownD8(0), UnknownDC(0), UnknownE0(0), UnknownE4(0),
      UnknownE8(0), UnknownEC(0), UnknownF0(0), UnknownF4(0),
      UnknownF8(0), UnknownFC(0), Unknown100(0), Unknown104(0),
      Unknown108(0), Unknown10C(0), Unknown110(0), Unknown114(0),
      Unknown118(0), Unknown11C(0), Unknown120(0), Unknown124(0),
      Unknown128(0), Unknown12C(0), Unknown130(0), Unknown134(0),
      Unknown138(0), Unknown13C(0), Unknown140(0), Unknown144(0)
{
}

// FUNCTION: 0x10ABB0E0 ??_GClass_10E6F3F4@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10ABA050's definition in this unit.
