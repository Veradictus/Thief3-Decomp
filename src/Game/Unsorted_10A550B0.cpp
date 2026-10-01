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
