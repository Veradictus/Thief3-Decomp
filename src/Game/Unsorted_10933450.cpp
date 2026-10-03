// Game/Unsorted_10933450.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

extern "C" void* memset(void* Dest, int Value, unsigned int Count);

// A COM object the list at +0x20 holds (Direct3D): slot 2 is Release.
class Class_109334E0_Element
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
};

// A list of pointers in a block: the first, last and end pointers at +0x08.
class Class_1095D6C0
{
public:
    void FUN_1095d6c0();

    ~Class_1095D6C0()
    {
        if (Unknown08)
            ::operator delete(Unknown08);
        Unknown08 = 0;
        Unknown0C = 0;
        Unknown10 = 0;
    }

    char Unknown00[8];
    Class_109334E0_Element** Unknown08;
    Class_109334E0_Element** Unknown0C;
    Class_109334E0_Element** Unknown10;
};

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49D1C
{
public:
    virtual ~Class_10E49D1C()
    {
        Unknown04 = 0;
        Unknown08 = -1;
        memset(&Unknown10, 0, sizeof(Unknown10));
        Unknown0C = 0;
    }

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
};

class Class_10E49DFC : public Class_10E49D1C
{
public:
    virtual ~Class_10E49DFC();

    int Unknown1C;
    Class_1095D6C0 Unknown20;
    int Unknown34;
    int Unknown38;
    Class_1095D6C0 Unknown3C;
};

// FUNCTION: 0x109334C0 ??_GClass_10E49DFC@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x109334E0's definition in this unit.

// FUNCTION: 0x109334E0 ??1Class_10E49DFC@@UAE@XZ
Class_10E49DFC::~Class_10E49DFC()
{
    Unknown3C.FUN_1095d6c0();
    Unknown34 = 0;
    Unknown38 = 0;
    Unknown1C = 0;
    for (Class_109334E0_Element** It = Unknown20.Unknown08; It != Unknown20.Unknown0C; ++It)
    {
        if (*It)
        {
            (*It)->Virtual2();
            *It = 0;
        }
    }
    Unknown20.FUN_1095d6c0();
}
