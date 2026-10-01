// Game/Unsorted_10C1F500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10FF667C
{
public:
    char Unknown00[0x4C];
    int Unknown4C;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E99370
{
public:
    Class_10E99370(int A, int B);
    ~Class_10E99370();

    virtual void FUN_10c28260();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

struct Struct_10C1F500
{
    Struct_10C1F500() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E991C4 : public Class_10E99370
{
public:
    Class_10E991C4(int A, int B);

    virtual void FUN_10c28260();

    Struct_10C1F500 Unknown10;
    char Unknown1C[0xC];
    int Unknown28;
    int Unknown2C;
    char Unknown30[0x24];
    int Unknown54;
    float Unknown58;
};

// FUNCTION: 0x10C1F500 ??0Class_10E991C4@@QAE@HH@Z
Class_10E991C4::Class_10E991C4(int A, int B)
    : Class_10E99370(A, B), Unknown28(0), Unknown2C(DAT_10ff667c->Unknown4C), Unknown54(0), Unknown58(1.0f)
{
}
