// Game/Unsorted_10C16250_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10FF667C_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int p1, int* p2);
};

class Class_10FF667C
{
public:
    char Unknown00[0x18];
    Class_10FF667C_Member* Unknown18;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E98C8C
{
public:
    virtual void FUN_10c162e0(int p1);

    int Unknown04;
};

class Class_10B3ED20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
};

class Class_10B228E0
{
public:
    char Unknown00[0x90];
    Class_10B3ED20* Unknown90;
};

class Class_10B1D1B0
{
public:
    Class_10B228E0* FUN_10b1d1b0();
};

class Class_10B1D660
{
public:
    char Unknown00[0x2C4];
    Class_10B1D1B0 Unknown2C4;
};

struct Struct_10AA3520
{
    char Unknown00[0xC];
    Class_10B1D660* Unknown0C;

    Class_10B1D660* GetUnknown0C() { return Unknown0C; }
};

extern Struct_10AA3520* DAT_10f35dec;

extern Class_10B228E0* DAT_10ff7084;

struct Struct_10C168D0
{
    char Unknown00[0x1C];
    unsigned int Unknown1C;
};

class Class_10C168D0
{
public:
    void FUN_10c168d0(Struct_10C168D0* P);

    char Unknown00[0xA4];
    Struct_10C168D0* UnknownA4;
};

// FUNCTION: 0x10C162E0 ?FUN_10c162e0@Class_10E98C8C@@UAEXH@Z
void Class_10E98C8C::FUN_10c162e0(int p1)
{
    DAT_10ff667c->Unknown18->Virtual1(p1, &Unknown04);
}

// FUNCTION: 0x10C16700 ?FUN_10c16700@@YA_NXZ
bool FUN_10c16700()
{
    if (!DAT_10ff7084)
        DAT_10ff7084 = DAT_10f35dec->GetUnknown0C()->Unknown2C4.FUN_10b1d1b0();
    return DAT_10ff7084->Unknown90->Virtual4() == 0xB;
}

// FUNCTION: 0x10C168D0 ?FUN_10c168d0@Class_10C168D0@@QAEXPAUStruct_10C168D0@@@Z
void Class_10C168D0::FUN_10c168d0(Struct_10C168D0* P)
{
    if (P && !(P->Unknown1C & 0x800000))
        UnknownA4 = P;
}
