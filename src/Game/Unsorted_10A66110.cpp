// Game/Unsorted_10A66110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

extern int DAT_10e6b594;

class Class_10A67B70 {
public:
    void FUN_10a67b70();
    void* Field00;
};

extern void* DAT_10e4dd6c[];

extern void* DAT_10e6b5a0[];

extern int DAT_10f11380;

class Class_10E6B5A0
{
public:
    Class_10E6B5A0* FUN_10a68b30();

    void* VTable;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Class_10A68B70 {
public:
    char Unknown00[0x14];
    int Field14;
    int FUN_10a68b70();
};

typedef void (*VFunc)(void);

class Class_10A69170 {
public:
    void FUN_10a69170();
};

class Class_10A6A140 {
public:
    void FUN_10a6a140();
    char Unknown00[4];
    unsigned char Field04;
};

void FUN_10a4c5f0();

extern void* DAT_10e6b978;

class Class_10a6da70
{
public:
    void FUN_10a6da70();
};

class Class_10A67000
{
public:
    bool FUN_10a67000(FVector V);
};

class Class_10E6BAB0
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
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual bool FUN_10a70fa0(const FVector& A, Class_10A67000* B);
};

extern void* DAT_10e6bbcc[];

class Class_10A74820 {
public:
    void* Field00;
    Class_10A74820* FUN_10a74820();
};

extern void* DAT_10e6bbe8[];

class Class_10A757A0
{
public:
    void* Field00;
public:
    void FUN_10a757a0();
};

// FUNCTION: 0x10A67B70 ?FUN_10a67b70@Class_10A67B70@@QAEXXZ
void Class_10A67B70::FUN_10a67b70()
{
    Field00 = (void*)&DAT_10e6b594;
}

// FUNCTION: 0x10A68B30 ?FUN_10a68b30@Class_10E6B5A0@@QAEPAV1@XZ
Class_10E6B5A0* Class_10E6B5A0::FUN_10a68b30()
{
    VTable = DAT_10e4dd6c;
    Unknown04 = 0x10;
    Unknown0C = 1;
    Unknown10 = DAT_10f11380++;
    VTable = DAT_10e6b5a0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    return this;
}

// FUNCTION: 0x10A68B70 ?FUN_10a68b70@Class_10A68B70@@QAEHXZ
int Class_10A68B70::FUN_10a68b70()
{
    return Field14 << 4;
}

// FUNCTION: 0x10A69170 ?FUN_10a69170@Class_10A69170@@QAEXXZ
void Class_10A69170::FUN_10a69170()
{
    VFunc* vtable = (VFunc*)*(VFunc**)this;
    vtable[7]();
}

// FUNCTION: 0x10A6A140 ?FUN_10a6a140@Class_10A6A140@@QAEXXZ
void Class_10A6A140::FUN_10a6a140()
{
    Field04 = 1;
}

// FUNCTION: 0x10A6ADF0 ?FUN_10a6adf0@@YAXXZ
void FUN_10a6adf0()
{
    FUN_10a4c5f0();
}

// FUNCTION: 0x10A6DA70 ?FUN_10a6da70@Class_10a6da70@@QAEXXZ
void Class_10a6da70::FUN_10a6da70() {
    *(void**)this = &DAT_10e6b978;
    FUN_10a4c5f0();
}

// FUNCTION: 0x10A70FA0 ?FUN_10a70fa0@Class_10E6BAB0@@UAE_NABVFVector@@PAVClass_10A67000@@@Z
bool Class_10E6BAB0::FUN_10a70fa0(const FVector& A, Class_10A67000* B)
{
    return B->FUN_10a67000(A);
}

// FUNCTION: 0x10A74820 ?FUN_10a74820@Class_10A74820@@QAEPAV1@XZ
Class_10A74820* Class_10A74820::FUN_10a74820()
{
    Field00 = DAT_10e6bbcc;
    return this;
}

// FUNCTION: 0x10A757A0 ?FUN_10a757a0@Class_10A757A0@@QAEXXZ
void Class_10A757A0::FUN_10a757a0()
{
    Field00 = (void*)DAT_10e6bbe8;
    FUN_10a4c5f0();
}
