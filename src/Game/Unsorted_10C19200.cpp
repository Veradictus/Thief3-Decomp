// Game/Unsorted_10C19200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern int DAT_10ff708c;

extern void* DAT_10e98cec[];

void FUN_10c62c90();

class Class_10C1A570
{
public:
    void* Field00;
    void FUN_10c1a570();
};

extern void* DAT_10e98d08[];

class Class_10C1A940 {
public:
    void FUN_10c1a940();
};

class Class_10C1A950
{
public:
    char Unknown00[0x20];
    float Field20;

    virtual float FUN_10c1a950();
};

class Class_10C1AAC0 {
public:
    char Unknown00[0x46];
    unsigned char Field46;
    unsigned char FUN_10c1aac0();
};

struct Struct_10C1AAD0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AAD0
{
public:
    bool FUN_10c1aad0(Struct_10C1AAD0* Out, float* Value);

    char Unknown00[0x48];
    Struct_10C1AAD0 Unknown48;
};

struct Struct_10C1ACA0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1ACA0
{
public:
    bool FUN_10c1aca0(Struct_10C1ACA0* Out, float* Value);

    char Unknown00[0x4C];
    Struct_10C1ACA0 Unknown4C;
};

struct Struct_10C1AD20
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AD20
{
public:
    bool FUN_10c1ad20(Struct_10C1AD20* Out, float* Value);

    char Unknown00[0x48];
    Struct_10C1AD20 Unknown48;
};

struct Struct_10C1AF80
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C1AF80
{
public:
    bool FUN_10c1af80(Struct_10C1AF80* Out, float* Value);

    char Unknown00[0xC];
    Struct_10C1AF80 Unknown0C;
};

void FUN_10c1b1a0();

extern void* DAT_10e8d7ac[];

class Class_10E8D7AC
{
public:
    Class_10E8D7AC();

    void** Unknown00;        // +0x00: DAT_10e8d7ac
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    char Unknown18;
    int Unknown1C;
    int Unknown20;
};

void FUN_10c1f820();

extern void* DAT_10ff7098;

struct OutputStruct_10C26670
{
    int field0;
    int field4;
    int field8;
};

struct Info_10C266A0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10E6AC20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual Class_1090A780 FUN_10c26a40();

    char Unknown04[0xC];
    Class_1090A780 Unknown10;
};

class Class_10C270B0 {
public:
    char Unknown00[0x44];
    unsigned char Field44;
    unsigned char FUN_10c270b0();
};

extern int DAT_10ff709c;

class Class_10E99370
{
public:
    Class_10E99370(int A, int B);

    virtual void FUN_10c28260();

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

extern int DAT_10ff70a0;

class Class_10c28ef0
{
public:
    char Unknown00[0x1d];
    unsigned char Field1D;
    int FUN_10c28ef0();
};

class Class_10C28F00
{
public:
    char Unknown00[0x4];
    int Field04;
    void FUN_10c28f00();
};

// FUNCTION: 0x10C1A160 ?FUN_10c1a160@@YAHXZ
int FUN_10c1a160()
{
    return DAT_10ff708c;
}

// FUNCTION: 0x10C1A570 ?FUN_10c1a570@Class_10C1A570@@QAEXXZ
void Class_10C1A570::FUN_10c1a570()
{
    Field00 = (void*)DAT_10e98cec;
    FUN_10c62c90();
}

// FUNCTION: 0x10C1A940 ?FUN_10c1a940@Class_10C1A940@@QAEXXZ
void Class_10C1A940::FUN_10c1a940()
{
    *(void**)this = (void*)DAT_10e98d08;
}

// FUNCTION: 0x10C1A950 ?FUN_10c1a950@Class_10C1A950@@UAEMXZ
float Class_10C1A950::FUN_10c1a950()
{
    return Field20;
}

// FUNCTION: 0x10C1AAC0 ?FUN_10c1aac0@Class_10C1AAC0@@QAEEXZ
unsigned char Class_10C1AAC0::FUN_10c1aac0()
{
    return Field46;
}

// FUNCTION: 0x10C1AAD0 ?FUN_10c1aad0@Class_10C1AAD0@@QAE_NPAUStruct_10C1AAD0@@PAM@Z
bool Class_10C1AAD0::FUN_10c1aad0(Struct_10C1AAD0* Out, float* Value)
{
    *Out = Unknown48;
    *Value = 16.0f;
    return true;
}

// FUNCTION: 0x10C1AB60 ?FUN_10c1ab60@@YAHXZ
int FUN_10c1ab60()
{
    return 0x100011;
}

// FUNCTION: 0x10C1ABC0 ?FUN_10c1abc0@@YAHXZ
int FUN_10c1abc0()
{
    return 0x100012;
}

// FUNCTION: 0x10C1AC50 ?FUN_10c1ac50@@YAHXZ
int FUN_10c1ac50()
{
    return 0x100013;
}

// FUNCTION: 0x10C1AC90 ?FUN_10c1ac90@@YAHXZ
int FUN_10c1ac90()
{
    return 0x100014;
}

// FUNCTION: 0x10C1ACA0 ?FUN_10c1aca0@Class_10C1ACA0@@QAE_NPAUStruct_10C1ACA0@@PAM@Z
bool Class_10C1ACA0::FUN_10c1aca0(Struct_10C1ACA0* Out, float* Value)
{
    *Out = Unknown4C;
    *Value = 0.0f;
    return true;
}

// FUNCTION: 0x10C1AD10 ?FUN_10c1ad10@@YAHXZ
int FUN_10c1ad10()
{
    return 0x1001ea;
}

// FUNCTION: 0x10C1AD20 ?FUN_10c1ad20@Class_10C1AD20@@QAE_NPAUStruct_10C1AD20@@PAM@Z
bool Class_10C1AD20::FUN_10c1ad20(Struct_10C1AD20* Out, float* Value)
{
    *Out = Unknown48;
    *Value = 0.0f;
    return true;
}

// FUNCTION: 0x10C1ADB0 ?FUN_10c1adb0@@YAHXZ
int FUN_10c1adb0()
{
    return 0x1002c5;
}

// FUNCTION: 0x10C1AF60 ?FUN_10c1af60@@YAHXZ
int FUN_10c1af60()
{
    return 0x100435;
}

// FUNCTION: 0x10C1AF70 ?FUN_10c1af70@@YAHXZ
int FUN_10c1af70()
{
    return 0x100447;
}

// FUNCTION: 0x10C1AF80 ?FUN_10c1af80@Class_10C1AF80@@QAE_NPAUStruct_10C1AF80@@PAM@Z
bool Class_10C1AF80::FUN_10c1af80(Struct_10C1AF80* Out, float* Value)
{
    *Out = Unknown0C;
    *Value = 0.0f;
    return true;
}

// FUNCTION: 0x10C1AFB0 ?FUN_10c1afb0@@YAHXZ
int FUN_10c1afb0()
{
    return 0x1005cd;
}

// FUNCTION: 0x10C1B7D0 ?FUN_10c1b7d0@@YAXXZ
void FUN_10c1b7d0()
{
    FUN_10c1b1a0();
}

// FUNCTION: 0x10C1D6A0 ??0Class_10E8D7AC@@QAE@XZ
Class_10E8D7AC::Class_10E8D7AC()
{
    Unknown00 = DAT_10e8d7ac;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
}

// FUNCTION: 0x10C1F980 ?FUN_10c1f980@@YAXXZ
void FUN_10c1f980()
{
    FUN_10c1f820();
}

// FUNCTION: 0x10C25570 ?FUN_10c25570@@YAPAXXZ
void* FUN_10c25570(void)
{
    return DAT_10ff7098;
}

// FUNCTION: 0x10C26670 ?FUN_10c26670@@YGXPAUOutputStruct_10C26670@@HHH@Z
void __stdcall FUN_10c26670(OutputStruct_10C26670* Out, int param2, int param3, int param4)
{
    Out->field0 = 0xffff - param2;
    Out->field4 = 0;
    Out->field8 = 0xffff - param3;
}

// FUNCTION: 0x10C266A0 ?FUN_10c266a0@@YGXPAUInfo_10C266A0@@HHH@Z
void __stdcall FUN_10c266a0(Info_10C266A0* Out, int A, int B, int C)
{
    Out->Unknown00 = C;
    Out->Unknown04 = 0xFFFF - A;
    Out->Unknown08 = B;
}

// FUNCTION: 0x10C26A40 ?FUN_10c26a40@Class_10E6AC20@@UAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10E6AC20::FUN_10c26a40()
{
    return Class_1090A780(Unknown10);
}

// FUNCTION: 0x10C270B0 ?FUN_10c270b0@Class_10C270B0@@QAEEXZ
unsigned char Class_10C270B0::FUN_10c270b0()
{
    return Field44;
}

// FUNCTION: 0x10C27900 ?FUN_10c27900@@YAHXZ
int FUN_10c27900()
{
    return DAT_10ff709c;
}

// FUNCTION: 0x10C28210 ??0Class_10E99370@@QAE@HH@Z
Class_10E99370::Class_10E99370(int A, int B)
{
    Unknown04 = A;
    Unknown08 = 0;
    Unknown0C = B;
}

// FUNCTION: 0x10C28BC0 ?FUN_10c28bc0@@YAHXZ
int FUN_10c28bc0()
{
    return DAT_10ff70a0;
}

// FUNCTION: 0x10C28EF0 ?FUN_10c28ef0@Class_10c28ef0@@QAEHXZ
int Class_10c28ef0::FUN_10c28ef0()
{
    return Field1D;
}

// FUNCTION: 0x10C28F00 ?FUN_10c28f00@Class_10C28F00@@QAEXXZ
void Class_10C28F00::FUN_10c28f00()
{
    Field04 = 0;
}
