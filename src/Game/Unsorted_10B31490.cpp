// Game/Unsorted_10B31490.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B315F0
{
    Struct_10B315F0() : Unknown00(0) {}

    int Unknown00;
};

class Class_10C3FF10
{
public:
    void FUN_10c3ff10(int A);
};

class Class_10C41420 : public Class_10C3FF10
{
};

Class_10C41420* FUN_10c47d90();

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x2C];
};

class Class_10E682F0 : public Class_10E67FD0
{
public:
    Class_10E682F0();

    virtual ~Class_10E682F0();

    void FUN_10a54d50();

    int Unknown118;
    int Unknown11C;
    char Unknown120;
    char Unknown121;
};

class Class_10E7BBC8 : public Class_10E682F0
{
public:
    Class_10E7BBC8();

    virtual ~Class_10E7BBC8();

    void FUN_10b31490();

    void (*Unknown124)(int);
    int Unknown128;
    Struct_10B315F0 Unknown12C;
    bool Unknown130;
    bool Unknown131;
    bool Unknown132;
    int Unknown134;
    bool Unknown138;
    int Unknown13C;
    int Unknown140;
    bool Unknown144;
};

// FUNCTION: 0x10B31490 ?FUN_10b31490@Class_10E7BBC8@@QAEXXZ
void Class_10E7BBC8::FUN_10b31490()
{
    FUN_10a54d50();
    if (Unknown144)
        FUN_10c47d90()->FUN_10c3ff10(-1);
    if (Unknown124)
    {
        Unknown124(Unknown128);
        Unknown128 = 0;
        Unknown124 = 0;
    }
}
