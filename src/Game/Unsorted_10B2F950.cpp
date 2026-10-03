// Game/Unsorted_10B2F950.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern const char DAT_10e47660[];

// Ion Storm's string (0x109081E0): a char pointer, null when default constructed.
class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E67FD0
{
public:
    Class_10E67FD0();

    virtual ~Class_10E67FD0();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x2C];
};

class Class_10E7B970 : public Class_10E67FD0
{
public:
    Class_10E7B970();

    virtual ~Class_10E7B970();

    int Unknown118;
    int Unknown11C;
    int Unknown120;
    int Unknown124;
    int Unknown128;
    int Unknown12C;
    int Unknown130;
    int Unknown134;
    Class_109081E0 Unknown138;
    int Unknown13C;
    int Unknown140;
    int Unknown144;
    int Unknown148;
    int Unknown14C;
    bool Unknown150;
    FString Unknown154;
    int Unknown160;
    bool Unknown164;
    int Unknown168;
    Class_109081E0 Unknown16C;
};

// FUNCTION: 0x10B2FB10 ??0Class_10E7B970@@QAE@XZ
Class_10E7B970::Class_10E7B970()
    : Unknown118(0), Unknown11C(0), Unknown120(0), Unknown124(0), Unknown128(0), Unknown12C(0), Unknown134(0),
      Unknown13C(0), Unknown140(0), Unknown144(0), Unknown148(0), Unknown14C(0), Unknown150(false), Unknown160(0),
      Unknown164(false), Unknown168(2), Unknown16C(DAT_10e47660)
{
    Unknown0E8 = 6;
}
