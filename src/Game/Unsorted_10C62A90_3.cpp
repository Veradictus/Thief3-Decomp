// Game/Unsorted_10C62A90_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9cb60;

struct Struct_10C62A90
{
    Struct_10C62A90() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E9CB60
{
public:
    Class_10E9CB60* FUN_10c62a90();
    Class_10E9CB60* FUN_10c62b10(const Class_10E9CB60& Other);

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    float Unknown18;
    float Unknown1C;
    bool Unknown20;
    Struct_10C62A90 Unknown24;
    float Unknown30;
    float Unknown34;
    float Unknown38;
    bool Unknown3C;
    int Unknown40;
    int Unknown44;
};

// FUNCTION: 0x10C62B10 ?FUN_10c62b10@Class_10E9CB60@@QAEPAV1@ABV1@@Z
Class_10E9CB60* Class_10E9CB60::FUN_10c62b10(const Class_10E9CB60& Other)
{
    Unknown00 = &DAT_10e9cb60;
    Unknown24.Struct_10C62A90::Struct_10C62A90();
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown20 = Other.Unknown20;
    Unknown30 = Other.Unknown30;
    Unknown34 = Unknown38 = -1.0f;
    Unknown3C = false;
    Unknown44 = -1;
    Unknown18 = 0.1f;
    Unknown1C = 1600.0f;
    Unknown0C = 0;
    Unknown40 = Other.Unknown40;
    return this;
}
