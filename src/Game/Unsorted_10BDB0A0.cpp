// Game/Unsorted_10BDB0A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, int Length);
};

class Class_10E8BE68
{
public:
    virtual void FUN_10bca010(FArchive& Ar);
};

void FUN_10c11ff0(FArchive& Ar, int* Value);

class Class_10E94A00 : public Class_10E8BE68
{
public:
    virtual void FUN_10bdb210(FArchive& Ar);

    char Unknown04[0x50];
    int Unknown54;
};

class Class_10E948D8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10bdb0e0();

    char Unknown04[0x3C];
    Class_10E948D8* Unknown40;
};

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BBDB40 : public Class_10AA82D0
{
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510();
};

class Class_10BB8700
{
public:
    void FUN_10bb8700();

    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

struct Struct_10BDB110
{
    char Unknown00[0xDC];
    unsigned char UnknownDC;
};

class Class_10E94E00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void FUN_10bdb110(int A);

    Class_10BB8700* Unknown04;
};

class Class_10BFF240
{
public:
    void FUN_10bff240(unsigned char A);
};

class Class_10BFF460 : public Class_10BFF240
{
public:
    bool FUN_10bff330();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
};

class Class_10E94578
{
public:
    virtual void FUN_10bdb0a0();

    void FUN_10bc5b50();
};

class Class_10E947B8 : public Class_10E94578
{
public:
    virtual void FUN_10bdb0a0();

    Class_10BBB410* Unknown04;
    char Unknown08[0x58];
    bool Unknown60;
    int Unknown64;
};

// FUNCTION: 0x10BDB0A0 ?FUN_10bdb0a0@Class_10E947B8@@UAEXXZ
void Class_10E947B8::FUN_10bdb0a0()
{
    Class_10BFF460* Obj = Unknown04->FUN_10bbb410();
    if (Obj)
    {
        if (!Obj->FUN_10bff330())
        {
            Obj->FUN_10bff240(1);
            FUN_10bc5b50();
        }
        else
        {
            ++Unknown64;
            Unknown60 = false;
        }
    }
}

// FUNCTION: 0x10BDB0E0 ?FUN_10bdb0e0@Class_10E948D8@@UAEXXZ
void Class_10E948D8::FUN_10bdb0e0()
{
    if (Unknown40)
        Unknown40->FUN_10bdb0e0();
}

// FUNCTION: 0x10BDB110 ?FUN_10bdb110@Class_10E94E00@@UAEXH@Z
void Class_10E94E00::FUN_10bdb110(int A)
{
    Struct_10BDB110* Object = (Struct_10BDB110*)Unknown04->Unknown08->FUN_10dbd510()->FUN_10aa82d0();
    if (Object->UnknownDC & 1)
        Unknown04->FUN_10bb8700();
}

// FUNCTION: 0x10BDB210 ?FUN_10bdb210@Class_10E94A00@@UAEXAAVFArchive@@@Z
void Class_10E94A00::FUN_10bdb210(FArchive& Ar)
{
    Class_10E8BE68::FUN_10bca010(Ar);
    FUN_10c11ff0(Ar, &Unknown54);
}
