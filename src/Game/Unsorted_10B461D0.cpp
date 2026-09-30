// Game/Unsorted_10B461D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10AC92F0
{
public:
    void FUN_10ac92f0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92F0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10DD7640
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A);
};

Class_10DD7640* FUN_10dd7640();

struct Info_10B49420
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

void FUN_10b3ae90();

class UnknownClass_10B4BD70 {
public:
    char Unknown00[0x450];
    int Unknown450;
};

extern void __stdcall FUN_10b4bd70(UnknownClass_10B4BD70* p1);

void FUN_10b3b130();

struct Struct_10B4D620
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B4D620
{
public:
    Struct_10B4D620 FUN_10b4d620();

    char Unknown00[0xEC];
    Struct_10B4D620 UnknownEC;
};

struct Info_10B4EC30
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

struct Info_10B4FBC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

void FUN_10a54cd0();

extern void* DAT_10e81620[];

class Class_10B3ACB0
{
public:
    void FUN_10b3acb0();

    void** Unknown00;
    char Unknown04[0x0C];
};

class Class_10E81620 : public Class_10B3ACB0
{
public:
    Class_10E81620* FUN_10b4fc90();

    float Unknown10;
    char Unknown14;
    float Unknown18;
};

struct Info_10B4FED0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

void FUN_10b3acd0();

extern void* DAT_10e816e0[];

class Class_10E816E0 : public Class_10B3ACB0
{
public:
    Class_10E816E0* FUN_10b53a30();

    char Unknown10[0x10];
    int Unknown20;
    int Unknown24;
    float Unknown28;
};

extern void FUN_10a51580(void);

extern void* DAT_10e81740[];

extern void* DAT_10e7edb8[];

class Class_10B53F70
{
public:
    void* vtable;
    char Unknown004[0xE4];
    int fieldE8;
    char Unknown0EC[0x2C];
    void* field118;

    Class_10B53F70* FUN_10b53f70();
};

extern void FUN_10a51620(void);

class Class_10B53FA0 {
public:
    char Unknown00[0x118];
    void* Unknown118;
    void FUN_10b53fa0();
};

void FUN_10a52a90();

void FUN_10b54070();

void FUN_10a5ab50();

// FUNCTION: 0x10B49170 ?FUN_10b49170@@YGXH@Z
void __stdcall FUN_10b49170(int Param)
{
    DAT_10f3a3d8->Unknown13C->FUN_10ac92f0();
    FUN_10dd7640()->Virtual2(0);
}

// FUNCTION: 0x10B49420 ?FUN_10b49420@@YGXPAUInfo_10B49420@@@Z
void __stdcall FUN_10b49420(Info_10B49420* Out)
{
    Out->Unknown00 = 0x3f9c;
    Out->Unknown04 = 0x4000;
    Out->Unknown08 = 0x4000;
    Out->Unknown0C = 0x2333;
    Out->Unknown10 = 0x2333;
}

// FUNCTION: 0x10B4BC20 ?FUN_10b4bc20@@YAXXZ
void FUN_10b4bc20()
{
    FUN_10b3ae90();
}

// FUNCTION: 0x10B4BD70 ?FUN_10b4bd70@@YGXPAVUnknownClass_10B4BD70@@@Z
void __stdcall FUN_10b4bd70(UnknownClass_10B4BD70* p1)
{
    p1->Unknown450 |= 0x10;
}

// FUNCTION: 0x10B4BDF0 ?FUN_10b4bdf0@@YAXXZ
void FUN_10b4bdf0()
{
    FUN_10b3b130();
}

// FUNCTION: 0x10B4CD10 ?FUN_10b4cd10@@YAHXZ
int FUN_10b4cd10()
{
    return 0x1f;
}

// FUNCTION: 0x10B4D620 ?FUN_10b4d620@Class_10B4D620@@QAE?AUStruct_10B4D620@@XZ
Struct_10B4D620 Class_10B4D620::FUN_10b4d620()
{
    return UnknownEC;
}

// FUNCTION: 0x10B4EC30 ?FUN_10b4ec30@@YGXPAUInfo_10B4EC30@@@Z
void __stdcall FUN_10b4ec30(Info_10B4EC30* Out)
{
    Out->Unknown00 = 0x2aaa;
    Out->Unknown04 = 0xaaa;
    Out->Unknown08 = 0x1fff;
    Out->Unknown0C = 0x2aaa;
    Out->Unknown10 = 0x2aaa;
}

// FUNCTION: 0x10B4FBC0 ?FUN_10b4fbc0@@YGXPAUInfo_10B4FBC0@@@Z
void __stdcall FUN_10b4fbc0(Info_10B4FBC0* Out)
{
    Out->Unknown00 = 0x3f9c;
    Out->Unknown04 = 0x3666;
    Out->Unknown08 = 0x4000;
    Out->Unknown0C = 0x3000;
    Out->Unknown10 = 0x3000;
}

// FUNCTION: 0x10B4FC80 ?FUN_10b4fc80@@YAXXZ
void FUN_10b4fc80()
{
    FUN_10a54cd0();
}

// FUNCTION: 0x10B4FC90 ?FUN_10b4fc90@Class_10E81620@@QAEPAV1@XZ
Class_10E81620* Class_10E81620::FUN_10b4fc90()
{
    FUN_10b3acb0();
    Unknown00 = DAT_10e81620;
    Unknown10 = 0.33f;
    Unknown14 = 0;
    Unknown18 = 10012.444f;
    return this;
}

// FUNCTION: 0x10B4FED0 ?FUN_10b4fed0@@YGXPAUInfo_10B4FED0@@@Z
void __stdcall FUN_10b4fed0(Info_10B4FED0* Out)
{
    Out->Unknown00 = 0x3f9c;
    Out->Unknown04 = 0x4000;
    Out->Unknown08 = 0x4000;
    Out->Unknown0C = 0x3000;
    Out->Unknown10 = 0x3000;
}

// FUNCTION: 0x10B4FF30 ?FUN_10b4ff30@@YAXXZ
void FUN_10b4ff30()
{
    FUN_10b3acd0();
}

// FUNCTION: 0x10B53A30 ?FUN_10b53a30@Class_10E816E0@@QAEPAV1@XZ
Class_10E816E0* Class_10E816E0::FUN_10b53a30()
{
    FUN_10b3acb0();
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown00 = DAT_10e816e0;
    Unknown28 = -1.0f;
    return this;
}

// FUNCTION: 0x10B53F70 ?FUN_10b53f70@Class_10B53F70@@QAEPAV1@XZ
Class_10B53F70* Class_10B53F70::FUN_10b53f70()
{
    FUN_10a51580();
    this->fieldE8 |= 0x10;
    this->vtable = (void*)DAT_10e81740;
    this->field118 = (void*)DAT_10e7edb8;
    return this;
}

// FUNCTION: 0x10B53FA0 ?FUN_10b53fa0@Class_10B53FA0@@QAEXXZ
void Class_10B53FA0::FUN_10b53fa0()
{
    *(void**)this = DAT_10e81740;
    Unknown118 = DAT_10e7edb8;
    FUN_10a51620();
}

// FUNCTION: 0x10B53FC0 ?FUN_10b53fc0@@YAXXZ
void FUN_10b53fc0()
{
    FUN_10a52a90();
}

// FUNCTION: 0x10B545D0 ?FUN_10b545d0@@YAXXZ
void FUN_10b545d0()
{
    FUN_10b54070();
}

// FUNCTION: 0x10B54960 ?FUN_10b54960@@YAXXZ
void FUN_10b54960()
{
    FUN_10a5ab50();
}
