// Game/Unsorted_10BD09D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_109081E0
{
public:
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0();

    void* Unknown00;
};

class Class_10E97B00
{
public:
    Class_10E97B00(const Class_10E97B00& Other);
    ~Class_10E97B00();

    virtual void FUN_10c01ff0(void* A);

    Class_109081E0 Unknown04;
};

class Class_10E9313C
{
public:
    Class_10E9313C(const Class_10E9313C& Other);

    virtual void FUN_10bd0190(int p1);
    virtual void FUN_10bd1240(FArchive& Ar);

    int Unknown04;
    Class_10E97B00 Unknown08;
    FVector Unknown10;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    bool Unknown30;
    Class_109081E0 Unknown34;
    bool Unknown38;
};

// FUNCTION: 0x10BD0B10 ??0Class_10E9313C@@QAE@ABV0@@Z
Class_10E9313C::Class_10E9313C(const Class_10E9313C& Other)
    : Unknown04(Other.Unknown04), Unknown08(Other.Unknown08), Unknown10(Other.Unknown10), Unknown1C(Other.Unknown1C),
      Unknown20(Other.Unknown20), Unknown24(Other.Unknown24), Unknown28(Other.Unknown28), Unknown2C(Other.Unknown2C),
      Unknown30(Other.Unknown30), Unknown34(Other.Unknown34), Unknown38(Other.Unknown38)
{
}
