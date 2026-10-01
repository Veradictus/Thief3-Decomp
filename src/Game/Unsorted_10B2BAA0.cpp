// Game/Unsorted_10B2BAA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef float FLOAT;

class FVector
{
public:
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}

    FLOAT X, Y, Z;
};

extern FVector DAT_10f032ec;

struct Struct_10B2BAA0
{
    Struct_10B2BAA0() : Unknown00(0) {}

    int Unknown00;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0x114];
};

class Class_10E7B360 : public Class_10E67FD0
{
public:
    Class_10E7B360();

    virtual ~Class_10E7B360();

    char Unknown118[0x4];
    int Unknown11C;
    char Unknown120[0x1C];
    int Unknown13C;
    char Unknown140[0x10];
    Struct_10B2BAA0 Unknown150;
    char Unknown154[0x4];
    FVector Unknown158;
    FLOAT Unknown164;
    FLOAT Unknown168;
    FLOAT Unknown16C;
    FLOAT Unknown170;
    bool Unknown174;
};

// FUNCTION: 0x10B2BAA0 ??0Class_10E7B360@@QAE@XZ
Class_10E7B360::Class_10E7B360()
    : Unknown11C(0), Unknown13C(0), Unknown174(true)
{
    Unknown158 = DAT_10f032ec;
    Unknown164 = 48.0f;
    Unknown168 = 18.0f;
    Unknown16C = 0.45f;
    Unknown170 = 0.5f;
}

// FUNCTION: 0x10B2BCE0 ??_GClass_10E7B360@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B2BAA0's definition in this unit.
