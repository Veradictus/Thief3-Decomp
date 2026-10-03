// Game/Unsorted_10BED4A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

double FUN_10c00480();

class Class_109081E0
{
public:
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0();

    void* Unknown00;
};

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);
    ~Class_10E90D70();

    virtual void Virtual0();

    int Unknown04[15];
};

// The base whose implicit destructor (0x10BD3140, a jmp to ~Class_10E90D70) unwinds this constructor.
class Class_10BD3140 : public Class_10E90D70
{
public:
    Class_10BD3140(int A, int B) : Class_10E90D70(A, B), Unknown40(true) {}

    bool Unknown40;
};

// 0x70 bytes; the vtable 0x10E97488.
class Class_10E97488 : public Class_10BD3140
{
public:
    Class_10E97488(int A, int B, const FVector& C, float D, const Class_109081E0& E, int F, int G, int H);

    float Unknown44;
    float Unknown48;
    FVector Unknown4C;
    int Unknown58;
    int Unknown5C;
    int Unknown60;
    int Unknown64;
    Class_109081E0 Unknown68;
    int Unknown6C;
};

// FUNCTION: 0x10BED9E0 ??0Class_10E97488@@QAE@HHABVFVector@@MABVClass_109081E0@@HHH@Z
Class_10E97488::Class_10E97488(int A, int B, const FVector& C, float D, const Class_109081E0& E, int F, int G, int H)
    : Class_10BD3140(A, B), Unknown44(FUN_10c00480() + D), Unknown48(D), Unknown4C(C), Unknown58(F), Unknown5C(0),
      Unknown60(0), Unknown64(G), Unknown68(E), Unknown6C(H)
{
}
