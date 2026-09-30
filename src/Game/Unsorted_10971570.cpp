// Game/Unsorted_10971570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e4df98[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10971A00
{
public:
    Class_109081E0 FUN_10971a00();
};

class Class_109737D0
{
public:
    Class_109737D0* FUN_109737d0(int p1);
};

void FUN_10a04100();

class Class_10E70A50
{
public:
    virtual void FUN_10adb3a0();

    char Unknown04[0x28];
};

class Class_10973E70 : public Class_10E70A50
{
public:
    void FUN_10973e70();

    char Unknown2C[0x58];
    int Field84;
};

class Class_10974300_Inner {
public:
    char Unknown00[0x4];
    void* Field04;
};

class Class_10974300 {
    char Unknown00[0x2C];
    Class_10974300_Inner* Field2C;
public:
    void* FUN_10974300();
};

class Class_10974340
{
public:
    char Unknown00[0x2c];
    int* Field2c;
    int FUN_10974340();
};

struct Target_10974580
{
    char Unknown00[0x218];
    unsigned int Unknown218Bits0To2 : 3;
    unsigned int Unknown218Bit3 : 1;
    unsigned int Unknown218Bits4To31 : 28;
};

struct Holder_10974580
{
    Target_10974580* Unknown00;
};

class Class_10974580
{
public:
    void FUN_10974580(int Value);

    char Unknown00[0x2C];
    Holder_10974580* Unknown2C;
};

class Class_10974a00_Member
{
public:
    virtual void F0() = 0;
    virtual void F1() = 0;
};

class Class_10974a00
{
public:
    char Unknown00[0x34];
    Class_10974a00_Member* Field34;
    void FUN_10974a00();
};

void FUN_1096ef10();

class Class_10976bf0
{
public:
    char Unknown00[0x124];
    float Field124;
    float FUN_10976bf0();
};

struct Struct_10976CE0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10976CE0
{
public:
    Struct_10976CE0 FUN_10976ce0();

    char Unknown00[0xE8];
    Struct_10976CE0 UnknownE8;
};

struct Struct_10976D10
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10976D10
{
public:
    Struct_10976D10 FUN_10976d10();

    char Unknown00[0xF4];
    Struct_10976D10 UnknownF4;
};

void FUN_10d3f330();

struct Class_10978090 {
    int unknown_00;
    int field_04;

    int FUN_10978090();
};

void FUN_1097e1e0();

// FUNCTION: 0x1097E230 ?FUN_1097e230@@YAXXZ
void FUN_1097e230()
{
    FUN_1097e1e0();
}
