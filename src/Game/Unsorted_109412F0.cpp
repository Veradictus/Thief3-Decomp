// Game/Unsorted_109412F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// Member function class structure
struct Class_109421A0
{
    char Unknown00[0xF0];
    int FieldF0;
    char UnknownF4[0x3C];
    void* Field130;

    void FUN_109421a0(int param1, int param2);
};

// Member function class structure
struct Class_109421C0
{
    char Unknown00[0xF0];
    int FieldF0;
    char UnknownF4[0x3C];
    void* Field130;

    void FUN_109421c0(int param1, int param2);
};

class Class_10943700
{
public:
    char Unknown00[0xF0];
    void* Field0F0;
    void* Get();
};

struct Elem_10943710
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

class Class_10943710
{
public:
    int* FUN_10943710(int Index);

    char Unknown00[0xF0];
    int UnknownF0;
    char UnknownF4[0x3C];
    Elem_10943710* Unknown130;
};

class Class_109437C0 {
public:
    char Unknown00[0x11c];
    float Field11c;

    float FUN_109437c0();
};

struct Struct_109437D0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_109437D0
{
public:
    Struct_109437D0 FUN_109437d0();

    char Unknown00[0x17C];
    Struct_109437D0 Unknown17C;
};

struct Struct_10943800
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10943800
{
public:
    Struct_10943800 FUN_10943800();

    char Unknown00[0x188];
    Struct_10943800 Unknown188;
};

class Class_10943970
{
public:
    int FUN_10943970();

    char Unknown00[0xE4];
    int UnknownE4;
    char UnknownE8[0x4];
    int UnknownEC;
    char UnknownF0[0xC];
    int UnknownFC;
    char Unknown100[0x4];
    int Unknown104;
};

struct Struct_10948220
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10948220
{
public:
    Struct_10948220 FUN_10948220();

    char Unknown00[0xCC];
    Struct_10948220 UnknownCC;
};

class Class_10948250 {
public:
    char Unknown00[0xd8];
    float FieldD8;

    float FUN_10948250();
};

class Class_1094AEC0 {
public:
    int Field00;
    unsigned char Field04;

    void FUN_1094aec0();
};

class Class_1094C700 {
public:
    char Unknown00[0x78];
    float Field78;

    float FUN_1094c700();
};

class Class_1094D950
{
public:
    Class_1094D950* FUN_1094d950();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    bool Unknown11;
    bool Unknown12;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Struct_1094D980
{
public:
    void SetValues(int Param1, int Param2, int Param3);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    char Unknown10;
    char Unknown11;
};

class Class_1094DA60
{
public:
    char Unknown00[0x150];
    unsigned char Field150;

    unsigned char FUN_1094da60();
};

class Class_1094DFA0
{
public:
    char Unknown00[0x110];
    int Field110;

    int FUN_1094dfa0();
};

struct Struct_1094E0F0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1094E0F0
{
public:
    Struct_1094E0F0 FUN_1094e0f0();

    char Unknown00[0x134];
    Struct_1094E0F0 Unknown134;
};

struct Struct_1094E120
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1094E120
{
public:
    Struct_1094E120 FUN_1094e120();

    char Unknown00[0x140];
    Struct_1094E120 Unknown140;
};

struct Elem_1094EF90
{
    int Unknown00;
    char Unknown04[0x1C];
    int Unknown20;
    char Unknown24[4];
};

class Class_1094EF90
{
public:
    int FUN_1094ef90(int Index);

    char Unknown00[0x108];
    Elem_1094EF90* Unknown108;
};

class Class_1094f9b0
{
public:
    char Unknown00[0x158];
    float Field158;
    float FUN_1094f9b0();
};

// FUNCTION: 0x109421A0 ?FUN_109421a0@Class_109421A0@@QAEXHH@Z
void Class_109421A0::FUN_109421a0(int param1, int param2)
{
    if (param1 >= FieldF0)
        return;

    void** ptr = (void**)Field130;
    int index = param1 * 9;
    ptr[index + 1] = (void*)param2;
}

// FUNCTION: 0x109421C0 ?FUN_109421c0@Class_109421C0@@QAEXHH@Z
void Class_109421C0::FUN_109421c0(int param1, int param2)
{
    if (param1 >= FieldF0)
        return;

    void** ptr = (void**)Field130;
    int index = param1 * 9;
    ptr[index + 2] = (void*)param2;
}

// FUNCTION: 0x10943700 ?Get@Class_10943700@@QAEPAXXZ
void* Class_10943700::Get()
{
    return Field0F0;
}

// FUNCTION: 0x10943710 ?FUN_10943710@Class_10943710@@QAEPAHH@Z
int* Class_10943710::FUN_10943710(int Index)
{
    if (Index < UnknownF0)
        return &Unknown130[Index].Unknown04;
    return 0;
}

// FUNCTION: 0x109437C0 ?FUN_109437c0@Class_109437C0@@QAEMXZ
float Class_109437C0::FUN_109437c0()
{
    return Field11c;
}

// FUNCTION: 0x109437D0 ?FUN_109437d0@Class_109437D0@@QAE?AUStruct_109437D0@@XZ
Struct_109437D0 Class_109437D0::FUN_109437d0()
{
    return Unknown17C;
}

// FUNCTION: 0x10943800 ?FUN_10943800@Class_10943800@@QAE?AUStruct_10943800@@XZ
Struct_10943800 Class_10943800::FUN_10943800()
{
    return Unknown188;
}

// FUNCTION: 0x10943970 ?FUN_10943970@Class_10943970@@QAEHXZ
int Class_10943970::FUN_10943970()
{
    return (UnknownFC + (Unknown104 + UnknownE4 * 2) * 8 + UnknownEC) * 2 + 0x1ac;
}

// FUNCTION: 0x10947420 ?FUN_10947420@@YAHXZ
int FUN_10947420()
{
    return 0x13;
}

// FUNCTION: 0x109474F0 ?FUN_109474f0@@YAHXZ
int FUN_109474f0()
{
    return 0x2;
}

// FUNCTION: 0x10948220 ?FUN_10948220@Class_10948220@@QAE?AUStruct_10948220@@XZ
Struct_10948220 Class_10948220::FUN_10948220()
{
    return UnknownCC;
}

// FUNCTION: 0x10948250 ?FUN_10948250@Class_10948250@@QAEMXZ
float Class_10948250::FUN_10948250()
{
    return FieldD8;
}

// FUNCTION: 0x10948E70 ?FUN_10948e70@@YAHXZ
int FUN_10948e70()
{
    return 0x238;
}

// FUNCTION: 0x1094AEC0 ?FUN_1094aec0@Class_1094AEC0@@QAEXXZ
void Class_1094AEC0::FUN_1094aec0()
{
    Field00 = 0;
    Field04 = 0;
}

// FUNCTION: 0x1094C700 ?FUN_1094c700@Class_1094C700@@QAEMXZ
float Class_1094C700::FUN_1094c700()
{
    return Field78;
}

// FUNCTION: 0x1094D950 ?FUN_1094d950@Class_1094D950@@QAEPAV1@XZ
Class_1094D950* Class_1094D950::FUN_1094d950()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0xff000000;
    Unknown10 = true;
    Unknown11 = false;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown12 = true;
    return this;
}

// FUNCTION: 0x1094D980 ?SetValues@Struct_1094D980@@QAEXHHH@Z
void Struct_1094D980::SetValues(int Param1, int Param2, int Param3)
{
    Unknown0C = Param3;
    Unknown10 = (char)Param1;
    Unknown11 = (char)Param2;
    Unknown04 = 0;
    Unknown08 = 0;
}

// FUNCTION: 0x1094DA60 ?FUN_1094da60@Class_1094DA60@@QAEEXZ
unsigned char Class_1094DA60::FUN_1094da60()
{
    return Field150;
}

// FUNCTION: 0x1094DFA0 ?FUN_1094dfa0@Class_1094DFA0@@QAEHXZ
int Class_1094DFA0::FUN_1094dfa0()
{
    return Field110;
}

// FUNCTION: 0x1094E0F0 ?FUN_1094e0f0@Class_1094E0F0@@QAE?AUStruct_1094E0F0@@XZ
Struct_1094E0F0 Class_1094E0F0::FUN_1094e0f0()
{
    return Unknown134;
}

// FUNCTION: 0x1094E120 ?FUN_1094e120@Class_1094E120@@QAE?AUStruct_1094E120@@XZ
Struct_1094E120 Class_1094E120::FUN_1094e120()
{
    return Unknown140;
}

// FUNCTION: 0x1094EF90 ?FUN_1094ef90@Class_1094EF90@@QAEHH@Z
int Class_1094EF90::FUN_1094ef90(int Index)
{
    return (Unknown108[Index].Unknown20 + (Unknown108[Index].Unknown20 & 1) + Unknown108[Index].Unknown00 * 2) * 16;
}

// FUNCTION: 0x1094F9B0 ?FUN_1094f9b0@Class_1094f9b0@@QAEMXZ
float Class_1094f9b0::FUN_1094f9b0()
{
    return Field158;
}
