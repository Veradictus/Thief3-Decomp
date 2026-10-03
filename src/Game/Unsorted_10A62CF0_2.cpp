// Game/Unsorted_10A62CF0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct FColor
{
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : B(InB), G(InG), R(InR), A(InA) {}

    BYTE B;
    BYTE G;
    BYTE R;
    BYTE A;
};

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E6B078
{
public:
    Class_10E6B078();

    virtual ~Class_10E6B078();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0xCC];
};

class Class_10E6A9F8 : public Class_10E6B078
{
public:
    Class_10E6A9F8();

    int Unknown1B8;
    int Unknown1BC;
    FColor Unknown1C0;
    FColor Unknown1C4;
    FString Unknown1C8;
    int Unknown1D4;
    int Unknown1D8;
    bool Unknown1DC;
    unsigned int Unknown1E0;
    int Unknown1E4;
    Class_109081E0 Unknown1E8;
};

// FUNCTION: 0x10A62E20 ??0Class_10E6A9F8@@QAE@XZ
Class_10E6A9F8::Class_10E6A9F8()
    : Unknown1B8(0), Unknown1BC(0), Unknown1C0(0xFF, 0xFF, 0x00), Unknown1C4(0xFF, 0xFF, 0xFF, 0x80), Unknown1D4(0),
      Unknown1D8(0), Unknown1DC(false), Unknown1E0(0x40), Unknown1E4(0), Unknown1E8("   ")
{
    Unknown0E8 = 2;
}
